/**
 * @author Maciej 'mac' Grzybek <mashester@gmail.com>
 * This part of code comes from repository authored by Maciej Grzybek and
 * available on github: https://github.com/maciejgrzybek/track0matic.
 * It is used with its author knowledge and acceptance.
 */

#ifndef DYNDBDRIVER_H
#define DYNDBDRIVER_H

#include <vector>
#include <set>
#include <string>
#include <sstream>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>

#include <pqxx/connection>
#include <pqxx/transaction>
#include <pqxx/transactor>
#include <pqxx/prepared_statement>

class Sensor;

namespace DB
{

namespace Common
{
class DBDriverOptions;
}

namespace exceptions
{

class DBException : public std::exception
{
public:
  virtual ~DBException() throw();
  virtual const char* what() const throw();
};

class NoResultAvailable : public DBException
{
public:
  virtual ~NoResultAvailable() throw();
  virtual const char* what() const throw();
};

} // namespace exceptions

class DynDBDriver
{
public:
  struct DR_row
  {
    DR_row(int sensor_id, int dr_id,
           double lon, double lat, double mos,
           time_t sensor_time, time_t upload_time = 0);

    int sensor_id;
    int dr_id;
    double lon;
    double lat;
    double mos;
    time_t upload_time;
    time_t sensor_time;
    Sensor* sensor; // TODO implement this, when needed: should fetch Sensor data from DB and produce it with SensorFactory
  };

  struct Track_row
  {
    Track_row(const boost::uuids::uuid& uuid,
              double lon, double lat, double mos,
              double lonVelocity, double latVelocity, double mosVelocity,
              double predictedLon, double predictedLat, double predictedMos,
              time_t refreshTime);

    static std::string uuidToString(const boost::uuids::uuid& uuid);

    boost::uuids::uuid uuid;

    double lon;
    double lat;
    double mos;

    double lonVelocity;
    double latVelocity;
    double mosVelocity;

    double predictedLon;
    double predictedLat;
    double predictedMos;

    time_t refreshTime;
  };

  struct Sensor_row
  {
    Sensor_row(int sensor_id,
               double lon, double lat, double mos,
               double range,
               const std::string& type);

    int sensor_id;
    double lon;
    double lat;
    double mos;
    double range;
    std::string type;
  };

  class DRCursor
  {
  public:
    /**
     * @brief DRCursor
     * @param dbdriver reference to DB driver, to be used for fetching rows
     * @param timestamp number of seconds from epoch start (01.01.1970) from where DRs are fetched
     * @param packetSize how many DRs are selected at once
     * @param ID of last retrieved DR - Cursor will obtain DRs with ID higher than given
     *  if -1 value given - option is disabled.
     *  This option is used to actively poll DB for new DRs,
     *  when no more result are yet available.
     */
    DRCursor(DynDBDriver* dbdriver,
             time_t timestamp = 0,
             unsigned packetSize = 20,
             int beforeFirstDRId = -1);

    /**
     * @brief fetchRow - return one row from iterator and advances.
     * @return DR_row from db, selected according startingTime_ and packetSize_
     */
    DR_row fetchRow();
    unsigned getPacketSize() const;

  private:
    /**
     * @brief timeToInt64 converts point time into int64 type,
     *  assuming ptime is in unix epoch.
     * @param pt ptime to convert
     * @return int64 containing timestamp.
     */
    static boost::int64_t timeToInt64(const boost::posix_time::ptime& pt);

    /**
     * @brief advancePacket method moves window for another packet of data
     *  It only sets offset, but does not affect DB
     *  If you would like to fetch data from next pack,
     *  use advancePacket() and fetchRow() later
     */
    void advancePacket();

    /**
     * @brief fetchRows executes prepared select with given parameters
     *  which are startingTime_ and packetSize_ (limit)
     */
    void fetchRows();

    DynDBDriver* dbdriver_;
    boost::posix_time::ptime startingTime_;
    unsigned packetSize_;
    unsigned offset_;

    bool resultInitialized_;
    pqxx::result::const_iterator resultIterator_;
    pqxx::result result_;
  };

  class TracksSnapshot
  {
  public:
    TracksSnapshot(DynDBDriver& dbDriver);

    void addTrack(const Track_row& track);
    std::size_t getTracksCount() const;
    void storeTracks();

  private:
    class Transactor : public pqxx::transactor<>
    {
    public:
      Transactor(unsigned long snapshotId,const std::vector<Track_row>& tracks);
      void operator()(pqxx::work& transaction);

    private:
      const unsigned long snapshotId_;
      const std::vector<Track_row> tracks_;
    };

    unsigned long getSnapshotIdFromSequence();

    DynDBDriver& dbDriver_;
    const unsigned long snapshotId_;
    std::vector<Track_row> tracks_;
  };

  /**
   * @brief C-tor for DynDBDriver, basing on external options file
   * @param path to configuration file
   * @deprecated use DynDBDriver(const DBDriverOptions&) instead.
   */
  DynDBDriver(const std::string& options_path);

  /**
   * @brief C-tor for DynDBDriver, basing on given options,
   *  loaded from configuration file
   * @param options - takes ownership
   */
  DynDBDriver(const Common::DBDriverOptions* options);
  ~DynDBDriver();

  DRCursor getDRCursor(time_t timestamp = 0,
                       unsigned packetSize = 20,
                       int beforeFirstDRId = -1);

  void insertDR(const DR_row& dr);

  TracksSnapshot getNewTracksSnapshot();

  std::set<Sensor_row*> getSensors();

private:
  void loadOptions(const std::string& options_path);

  const Common::DBDriverOptions* options_;
  pqxx::connection* db_connection_;
};

} // namespace DB

#endif // DYNDBDRIVER_H
