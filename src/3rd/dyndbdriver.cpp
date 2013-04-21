#include <memory>
#include <fstream>
#include <string>

#include <boost/archive/xml_archive_exception.hpp>
#include <boost/archive/xml_iarchive.hpp>

#include <pqxx/connection>
#include <pqxx/transaction>

#include "dyndbdriver.h"

namespace DB
{

DynDBDriver::DynDBDriver(const std::string& options_path)
{
  { // read configuration from file
    std::ifstream ifs(options_path.c_str());
    boost::archive::xml_iarchive ia(ifs);
    try
    {
      ia >> boost::serialization::make_nvp("DB_options",options_);
    }
    catch (const boost::archive::xml_archive_exception& ex)
    {
      std::cerr << "Configuration file is corrupted: " << ex.what() << std::endl;
      throw;
    }
  }
  db_connection_ = new pqxx::connection(options_.toString());
}

DynDBDriver::~DynDBDriver()
{
  delete db_connection_;
}

DynDBDriver::DRCursor DynDBDriver::getDRCursor(time_t timestamp,
                                               unsigned packetSize,
                                               int beforeFirstDRId)
{
  return DRCursor(this,timestamp,packetSize,beforeFirstDRId);
}

void DynDBDriver::insertDR(const DR_row& dr)
{
  std::string sql;
  if (dr.dr_id == -1) // TODO change this magic constant
  { // get dr_id from DB's sequence
      sql = "INSERT INTO detection_reports "
        "(sensor_id,lon,lat,meters_over_sea,upload_time,sensor_time) "
        "VALUES("
          + pqxx::to_string(dr.sensor_id) + ","
          + pqxx::to_string(dr.lon) + ","
          + pqxx::to_string(dr.lat) + ","
          + pqxx::to_string(dr.mos) + ","
        + "to_timestamp(" + pqxx::to_string(dr.upload_time) + "),"
        + "to_timestamp(" + pqxx::to_string(dr.sensor_time) + "))";
  }
  else
  { // dr_id given
    sql = "INSERT INTO detection_reports "
      "(sensor_id,dr_id,lon,lat,meters_over_sea,upload_time,sensor_time) "
      "VALUES("
        + pqxx::to_string(dr.sensor_id) + ","
        + pqxx::to_string(dr.dr_id) + ","
        + pqxx::to_string(dr.lon) + ","
        + pqxx::to_string(dr.lat) + ","
        + pqxx::to_string(dr.mos) + ","
      + "to_timestamp(" + pqxx::to_string(dr.upload_time) + "),"
      + "to_timestamp(" + pqxx::to_string(dr.sensor_time) + "))";
  }

  pqxx::work t(*db_connection_,"DR inserter");
  t.exec(sql);
  t.commit();
}

std::set<Sensor*> DynDBDriver::getSensors()
{
}

DynDBDriver::DBDriverOptions::DBDriverOptions(const std::string& host,
                                              const std::string& port,
                                              const std::string& dbname,
                                              const std::string& user,
                                              const std::string& password,
                                              unsigned int connection_timeout,
                                              const std::string& additional_options,
                                              SSLMode ssl_mode,
                                              const std::string& service)
  : host(host),
    port(port),
    dbname(dbname),
    username(user),
    password(password),
    connection_timeout(connection_timeout),
    additional_options(additional_options),
    ssl_mode(ssl_mode),
    service(service)
{}

std::string DynDBDriver::DBDriverOptions::toString() const
{
  std::string conn_timeout = boost::lexical_cast<std::string>(connection_timeout);
  std::string sslMode = sslModeToString();
  std::string result;
  if (!host.empty())
    result += "host='"+host+"' ";
  if (!port.empty())
    result += "port='"+port+"' ";
  if (!dbname.empty())
    result += "dbname='"+dbname+"' ";
  if (!username.empty())
    result += "user='"+username+"' ";
  if (!password.empty())
    result += "password='"+password+"' ";
  if (!conn_timeout.empty())
    result += "connect_timeout='"+conn_timeout+"' ";
  if (!additional_options.empty())
    result += "options='"+additional_options+"' ";
  if (!sslMode.empty())
    result += "sslmode='"+sslMode+"' ";
  if (!service.empty())
    result += "service='"+service+"'";

  return result;
}

std::string DynDBDriver::DBDriverOptions::sslModeToString() const
{
  switch (ssl_mode)
  {
    case DisableSSL:
      return "disable";
      break;
    case AllowSSL:
      return "allow";
      break;
    case RequireSSL:
      return "require";
      break;
    default:
    case PreferSSL:
      return "prefer";
      break;
  }
}

} // namespace DB
