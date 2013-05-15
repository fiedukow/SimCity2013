/**
 * @author Maciej 'mac' Grzybek <mashester@gmail.com>
 * This part of code comes from repository authored by Maciej Grzybek and
 * available on github: https://github.com/maciejgrzybek/track0matic.
 * It is used with its author knowledge and acceptance.
 */

#include "dyndbdriver.h"

#include <fstream>
#include <memory>
#include <string>

#include <boost/lexical_cast.hpp> // for Track_row::uuidToString method
#include <boost/uuid/uuid_io.hpp> // for Track_row::uuidToString method

#include <pqxx/connection>
#include <pqxx/transaction>

#include "common.h"
#include "logger.h"

namespace DB
{

namespace exceptions
{

DBException::~DBException() throw()
{}

const char* DBException::what() const throw()
{
  return "Unknown DB driver exception.";
}

NoResultAvailable::~NoResultAvailable() throw()
{}

const char* NoResultAvailable::what() const throw()
{
  return "No result available - maybe empty result.";
}

} // namespace exceptions

/******************************************************************************/

DynDBDriver::DR_row::DR_row(int sensor_id,
                                int dr_id,
                                double lon,
                                double lat,
                                double mos,
                                time_t sensor_time,
                                time_t upload_time)
  : sensor_id(sensor_id),dr_id(dr_id),
    lon(lon),lat(lat),mos(mos),
    upload_time(upload_time),sensor_time(sensor_time)
{}

/******************************************************************************/

DynDBDriver::Track_row::Track_row(const boost::uuids::uuid& uuid,
                                  double lon, double lat, double mos,
                                  double lonVelocity,
                                  double latVelocity,
                                  double mosVelocity,
                                  double predictedLon,
                                  double predictedLat,
                                  double predictedMos, time_t refreshTime)
  : uuid(uuid),
    lon(lon),lat(lat),mos(mos),
    lonVelocity(lonVelocity),latVelocity(latVelocity),mosVelocity(mosVelocity),
    predictedLon(predictedLon),
    predictedLat(predictedLat),
    predictedMos(predictedMos),
    refreshTime(refreshTime)
{}

std::string DynDBDriver::Track_row::uuidToString(const boost::uuids::uuid& uuid)
{
  std::string result;
  try
  {
    result = boost::lexical_cast<std::string>(uuid);
  }
  catch (const boost::bad_lexical_cast&)
  {
    ::Common::GlobalLogger::getInstance()
        .log("DynDBDriver","Failed casting track's UUID to string");
  }

  return result; // if fails to cast, returns empty
}

/******************************************************************************/

DynDBDriver::DRCursor::DRCursor(DynDBDriver* dbdriver, time_t timestamp,
                                unsigned packetSize, int beforeFirstDRId)
  : dbdriver_(dbdriver),
    packetSize_(packetSize),
    offset_(0),
    resultInitialized_(false)
{
  startingTime_ = boost::posix_time::from_time_t(timestamp);

  std::stringstream sql;
  if (beforeFirstDRId > -1)
  {
    sql << "SELECT *,"
          "extract(epoch from upload_time) as upl_ts,"
          "extract(epoch from sensor_time) as sns_ts "
          "FROM detection_reports WHERE "
          "sensor_time >= to_timestamp($1) AND dr_id > "
          << beforeFirstDRId << " "
          << "ORDER BY sensor_time ASC, upload_time ASC "
             "LIMIT $2 OFFSET $3";
  }
  else
  {
    sql << "SELECT *,"
          "extract(epoch from upload_time) as upl_ts,"
          "extract(epoch from sensor_time) as sns_ts "
          "FROM detection_reports WHERE "
          "sensor_time >= to_timestamp($1) "
          "ORDER BY sensor_time ASC, upload_time ASC "
          "LIMIT $2 OFFSET $3";
  }

  // prepare statement (query) for connection
  dbdriver->db_connection_->unprepare("DR_select_statement");
  dbdriver->db_connection_->prepare("DR_select_statement",sql.str());
}

DynDBDriver::DR_row DynDBDriver::DRCursor::fetchRow()
{
  if (!resultInitialized_)
    fetchRows();
  else if (resultIterator_ == result_.end()) // no more rows to fetch
  {
    advancePacket();
    fetchRows();
  }
  pqxx::result::const_iterator row = resultIterator_++;
  return DR_row(row[0].as<int>(), // sensor_id
                row[1].as<int>(), // dr_id
                row[2].as<double>(), // lon
                row[3].as<double>(), // lat
                row[4].as<double>(), // meters_over_sea
                row[8].as<double>(), // sensor_time - like above
                row[7].as<double>()); // upload_time - read as double, because of microseconds
}

unsigned DynDBDriver::DRCursor::getPacketSize() const
{
  return packetSize_;
}

boost::int64_t
  DynDBDriver::DRCursor::timeToInt64(const boost::posix_time::ptime& pt)
{
  using namespace boost::posix_time;
  static ptime epoch(boost::gregorian::date(1970, 1, 1));
  time_duration diff(pt - epoch);
  return (diff.ticks() / diff.ticks_per_second());
}

void DynDBDriver::DRCursor::advancePacket()
{
  offset_ += packetSize_;
}

void DynDBDriver::DRCursor::fetchRows()
{
  pqxx::work t(*dbdriver_->db_connection_,"DRs fetcher");
  { // TODO rewrite this, when logger will be more sophisticated
    std::stringstream msg;
    msg << "Fetching rows with starting time = "
        << timeToInt64(startingTime_)
        << " packet size = " << packetSize_
        << " offset = " << offset_;
    ::Common::GlobalLogger::getInstance().log("DynDBDriver",msg.str());
  }
  result_
      = t.prepared("DR_select_statement")
      (pqxx::to_string(timeToInt64(startingTime_)))
      (packetSize_)
      (offset_).exec();

  { // TODO rewrite this, when logger will be more sophisticated
    std::stringstream msg;
    msg << "Fetched " << result_.size() << " rows";
    ::Common::GlobalLogger::getInstance().log("DynDBDriver",msg.str());
  }

  resultIterator_ = result_.begin();
  if (resultIterator_ == result_.end()) // if after fetching, result is empty - tell interested ones.
    throw DB::exceptions::NoResultAvailable();

  resultInitialized_ = true;
}

/******************************************************************************/

DynDBDriver::Sensor_row::Sensor_row(int sensor_id,
                                    double lon, double lat, double mos,
                                    double range,
                                    const std::string& type)
  : sensor_id(sensor_id),
    lon(lon),lat(lat),mos(mos),
    range(range),
    type(type)
{}

/******************************************************************************/

DynDBDriver::TracksSnapshot
::Transactor::Transactor(unsigned long snapshotId,
                         const std::vector<DynDBDriver::Track_row>& tracks)
  : snapshotId_(snapshotId),
    tracks_(tracks)
{}

void DynDBDriver
  ::TracksSnapshot::Transactor::operator()(pqxx::work& transaction)
{
  for (const DynDBDriver::Track_row& track : tracks_)
  {
    const std::string sql = "INSERT INTO track_snapshots "
        "(snapshot_id,track_id,lon,lat,meters_over_sea,"
        "lon_velocity,lat_velocity,meters_over_sea_velocity,"
        "predicted_lon,predicted_lat,predicted_meters_over_sea,"
        "refresh_time) "
        "VALUES("
        + pqxx::to_string(snapshotId_) + ",'"
        + pqxx::to_string(Track_row::uuidToString(track.uuid)) + "',"
        + pqxx::to_string(track.lon) + ","
        + pqxx::to_string(track.lat) + ","
        + pqxx::to_string(track.mos) + ","
        + pqxx::to_string(track.lonVelocity) + ","
        + pqxx::to_string(track.latVelocity) + ","
        + pqxx::to_string(track.mosVelocity) + ","
        + pqxx::to_string(track.predictedLon) + ","
        + pqxx::to_string(track.predictedLat) + ","
        + pqxx::to_string(track.predictedMos) + ","
        + "to_timestamp(" + pqxx::to_string(track.refreshTime) + "))";
    transaction.exec(sql);
  }

  transaction.commit();
}

/******************************************************************************/

DynDBDriver::TracksSnapshot::TracksSnapshot(DynDBDriver& dbDriver)
  : dbDriver_(dbDriver),
    snapshotId_(getSnapshotIdFromSequence())
{}

void DynDBDriver::TracksSnapshot::addTrack(const DynDBDriver::Track_row& track)
{
  tracks_.push_back(track);
}

std::size_t DynDBDriver::TracksSnapshot::getTracksCount() const
{
  return tracks_.size();
}

void DynDBDriver::TracksSnapshot::storeTracks()
{
  Transactor trans(snapshotId_,tracks_);
  dbDriver_.db_connection_->perform(trans); // let pqxx perform transaction
}

unsigned long DynDBDriver::TracksSnapshot::getSnapshotIdFromSequence()
{
  const std::string sql
      = "SELECT nextval('track_snapshot_seq')";

  pqxx::work t(*dbDriver_.db_connection_,"Track snapshot id fetcher");
  pqxx::result result = t.exec(sql);
  return result[0][0].as<unsigned long>();
}

/******************************************************************************/

DynDBDriver::DynDBDriver(const std::string& options_path)
{
  loadOptions(options_path);
  db_connection_ = new pqxx::connection(options_->toString());
}

DynDBDriver::DynDBDriver(const Common::DBDriverOptions* options)
  : options_(options)
{
  db_connection_ = new pqxx::connection(options_->toString());
}

DynDBDriver::~DynDBDriver()
{
  delete db_connection_;
  delete options_;
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
          + ((dr.upload_time == 0)
             ? "DEFAULT"
             : ("to_timestamp(" + pqxx::to_string(dr.upload_time) + ")"))
          + ",to_timestamp(" + pqxx::to_string(dr.sensor_time) + "))";
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
        + ((dr.upload_time == 0)
           ? "DEFAULT"
           : ("to_timestamp(" + pqxx::to_string(dr.upload_time) + ")"))
        + ",to_timestamp(" + pqxx::to_string(dr.sensor_time) + "))";
  }

  pqxx::work t(*db_connection_,"DR inserter");
  t.exec(sql);
  t.commit();
}

DynDBDriver::TracksSnapshot DynDBDriver::getNewTracksSnapshot()
{
  return TracksSnapshot(*this);
}

std::set<DynDBDriver::Sensor_row*> DynDBDriver::getSensors()
{
  const std::string sql
      = "SELECT s.sensorid,s.lon,s.lat,s.mos,s.range,st.typename "
        "FROM sensors as s, sensortypes as st "
        "WHERE s.typeid = st.typeid";

  pqxx::work t(*db_connection_,"Sensors fetcher");
  pqxx::result result = t.exec(sql);

  pqxx::result::const_iterator resultIterator = result.begin();
  if (resultIterator == result.end()) // if after fetching, result is empty - tell interested ones.
    throw DB::exceptions::NoResultAvailable();

  std::set<Sensor_row*> resultSet;

  for (; resultIterator != result.end(); ++resultIterator)
  {
    pqxx::result::const_iterator row = resultIterator;
    Sensor_row* sensor
        = new Sensor_row(row[0].as<int>(),
                         row[1].as<double>(),
                         row[2].as<double>(),
                         row[3].as<double>(),
                         row[4].as<double>(),
                         row[5].as<std::string>());
    resultSet.insert(sensor);
  }

  return resultSet;
}

void DynDBDriver::loadOptions(const std::string& options_path)
{
  std::unique_ptr<Common::DBDriverOptions> opts
      = Common::loadOptionsFromFile(options_path);
  options_ = opts.release();
}

} // namespace DB
