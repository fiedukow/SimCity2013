/**
 * @author Maciej 'mac' Grzybek <mashester@gmail.com>
 * This part of code comes from repository authored by Maciej Grzybek and
 * available on github: https://github.com/maciejgrzybek/track0matic.
 * It is used with its author knowledge and acceptance.
 */

#include "common.h"

#include <fstream>

#include <boost/archive/xml_archive_exception.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/lexical_cast.hpp>

namespace DB
{

namespace Common
{

std::unique_ptr<DBDriverOptions>
  loadOptionsFromFile(const std::string& options_path)
{
  DBDriverOptions read;
  // read configuration from file
  std::ifstream ifs(options_path.c_str());
  boost::archive::xml_iarchive ia(ifs);
  try
  {
    ia >> boost::serialization::make_nvp("DB_options",read);
  }
  catch (const boost::archive::xml_archive_exception& ex)
  {
    std::cerr << "Configuration file is corrupted: " << ex.what() << std::endl;
    throw;
  }

  return std::unique_ptr<DBDriverOptions>(new DBDriverOptions(read));
}

DBDriverOptions::DBDriverOptions(const std::string& host,
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


std::string DBDriverOptions::toString() const
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

std::string DBDriverOptions::sslModeToString() const
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

} // namespace Common

} // namespace DB
