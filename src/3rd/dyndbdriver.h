#ifndef DYNDBDRIVER_H
#define DYNDBDRIVER_H

#include <vector>
#include <set>
#include <string>
#include <sstream>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/lexical_cast.hpp>

#include <pqxx/connection>
#include <pqxx/transaction>
#include <pqxx/prepared_statement>

class Sensor;

namespace DB
{

namespace exceptions
{
  class DBException : public std::exception
  {
  public:
    virtual ~DBException() throw()
    {}

    virtual const char* what() const throw()
    {
      return "Unknown DB driver exception.";
    }
  };

  class NoResultAvailable : public DBException
  {
  public:
    virtual ~NoResultAvailable() throw()
    {}

    virtual const char* what() const throw()
    {
      return "No result available - maybe empty result.";
    }

  };
} // namespace exceptions

class DynDBDriver
{
public:
  struct DR_row
  {
    DR_row(int sensor_id,
           int dr_id,
           double lon,
           double lat,
           double mos,
           time_t upload_time,
           time_t sensor_time)
      : sensor_id(sensor_id),
        dr_id(dr_id),
        lon(lon),
        lat(lat),
        mos(mos),
        upload_time(upload_time),
        sensor_time(sensor_time)
    {}

    int sensor_id;
    int dr_id;
    double lon;
    double lat;
    double mos;
    time_t upload_time;
    time_t sensor_time;
    Sensor* sensor; // TODO implement this, when needed: should fetch Sensor data from DB and produce it with SensorFactory
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
             int beforeFirstDRId = -1)
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

    /**
     * @brief fetchRow - return one row from iterator and advances.
     * @return DR_row from db, selected according startingTime_ and packetSize_
     */
    DR_row fetchRow()
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
                    row[7].as<double>(), // upload_time - read as double, because of microseconds
                    row[8].as<double>()); // sensor_time - like above
    }

    unsigned getPacketSize() const
    {
      return packetSize_;
    }

  private:
    /**
     * @brief timeToInt64 converts point time into int64 type,
     *  assuming ptime is in unix epoch.
     * @param pt ptime to convert
     * @return int64 containing timestamp.
     */
    static boost::int64_t timeToInt64(const boost::posix_time::ptime& pt)
    {
      using namespace boost::posix_time;
      static ptime epoch(boost::gregorian::date(1970, 1, 1));
      time_duration diff(pt - epoch);
      return (diff.ticks() / diff.ticks_per_second());
    }

    /**
     * @brief advancePacket method moves window for another packet of data
     *  It only sets offset, but does not affect DB
     *  If you would like to fetch data from next pack,
     *  use advancePacket() and fetchRow() later
     */
    void advancePacket()
    {
      offset_ += packetSize_;
    }

    /**
     * @brief fetchRows executes prepared select with given parameters
     *  which are startingTime_ and packetSize_ (limit)
     */
    void fetchRows()
    {
      pqxx::work t(*dbdriver_->db_connection_,"DRs fetcher");
      { // TODO rewrite this, when logger will be more sophisticated
        std::stringstream msg;
        msg << "Fetching rows with starting time = "
            << timeToInt64(startingTime_)
            << " packet size = " << packetSize_
            << " offset = " << offset_;
      }
      result_
          = t.prepared("DR_select_statement")
          (pqxx::to_string(timeToInt64(startingTime_)))
          (packetSize_)
          (offset_).exec();

      { // TODO rewrite this, when logger will be more sophisticated
        std::stringstream msg;
        msg << "Fetched " << result_.size() << " rows";
      }

      resultIterator_ = result_.begin();
      if (resultIterator_ == result_.end()) // if after fetching, result is empty - tell interested ones.
        throw DB::exceptions::NoResultAvailable();

      resultInitialized_ = true;
    }

    DynDBDriver* dbdriver_;
    boost::posix_time::ptime startingTime_;
    unsigned packetSize_;
    unsigned offset_;

    bool resultInitialized_;
    pqxx::result::const_iterator resultIterator_;
    pqxx::result result_;
  };

  struct Sensor_row
  {
    Sensor_row(int sensor_id,
               double lon,
               double lat,
               double mos,
               double range,
               std::string type)
      : sensor_id(sensor_id),
        lon(lon),
        lat(lat),
        mos(mos),
        range(range),
        type(type)
    {}

    int sensor_id;
    double lon;
    double lat;
    double mos;
    double range;
    std::string type;
  };

  DynDBDriver(const std::string& options_path);
  ~DynDBDriver();

  DRCursor getDRCursor(time_t timestamp = 0,
                       unsigned packetSize = 20,
                       int beforeFirstDRId = -1);

  void insertDR(const DR_row& dr);

  std::set<class Sensor*> getSensors();

private:
  class DBDriverOptions
  {
  public:
    /* SSLMode can be:
        DisableSSL - SSL is not used when connecting to DB
        AllowSSL - non-SSL connection is tried first, on fail, SSL goes on
        PreferSSL - first SSL connection is tried, when failed, non-SSL connection is tried [DEFAULT VALUE]
        RequireSSL - when SSL connection fails, error is raised
    */
    enum SSLMode { DisableSSL, AllowSSL, PreferSSL, RequireSSL };

    DBDriverOptions(const std::string& host = "host",
                    const std::string& port = "5432",
                    const std::string& dbname = "",
                    const std::string& user = "",
                    const std::string& password = "",
                    unsigned int connection_timeout = 0,
                    const std::string& additional_options = "",
                    SSLMode ssl_mode = PreferSSL,
                    const std::string& service = "");

    std::string toString() const;

    // if any option is empty, default will be used
    std::string host; // DB hostname; if starts with slash ("/"), means unix socket; default is "localhost"
    std::string port; // port or socket file name extension for Unix-domain connections.
    std::string dbname; // dbname; default is the same as username
    std::string username; // username used to authenticate to DB
    std::string password; // password used to authenticate to DB
    unsigned int connection_timeout; // connection timeout, when empty (0) - connector will wait indefinitely. timeout less than 2s is not recommended
    std::string additional_options; // additional options to pass to DB when connecting
    enum SSLMode ssl_mode; // read above explaination of SSLMode enum
    std::string service; // service name to use for additional parameters (maintained centrally)

  private:
    friend class boost::serialization::access;

    std::string sslModeToString() const;

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      using boost::serialization::make_nvp;
      ar & make_nvp("Host",host);
      ar & make_nvp("Port",port);
      ar & make_nvp("DBName",dbname);
      ar & make_nvp("Username",username);
      ar & make_nvp("Password",password);
      ar & make_nvp("Connection_timeout",connection_timeout);
      ar & make_nvp("Additional_options",additional_options);
      ar & make_nvp("SSL_mode",ssl_mode);
      ar & make_nvp("Service",service);
    }
  };

  DBDriverOptions options_;
  pqxx::connection* db_connection_;
};

} // namespace DB

#endif // DYNDBDRIVER_H
