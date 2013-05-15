/**
 * @author Maciej 'mac' Grzybek <mashester@gmail.com>
 * This part of code comes from repository authored by Maciej Grzybek and
 * available on github: https://github.com/maciejgrzybek/track0matic.
 * It is used with its author knowledge and acceptance.
 */

#ifndef DB_COMMON_H
#define DB_COMMON_H

#include <memory>
#include <string>

#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>

namespace DB
{

namespace Common
{

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
  void serialize(Archive& ar, const unsigned int /*version*/)
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

std::unique_ptr<DBDriverOptions>
  loadOptionsFromFile(const std::string& options_path);

} // namespace Common

} // namespace DB

#endif // DB_COMMON_H
