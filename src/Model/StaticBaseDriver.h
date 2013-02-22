#ifndef STATICBASEDRIVER_H
#define STATICBASEDRIVER_H

#include <string>
#include <pqxx/pqxx>

class StaticBaseDriver
{
public:
  StaticBaseDriver(const char* connectionDetails = "",
                   bool persistent = true);
  ~StaticBaseDriver();

private:
  /*
   * Connect to RDBMS if connection isn't already established
   * throws an exception if failed.
   *
   * @returns bool - true if connection was established now
   *                 or false if it was already created earlier.
   * @throw GeneralException - if an exception occured while
   *                           trying to connect to RDBMS
   */
  bool ensureDBConnection();
  void connect();
  void disconnect();

private:
  const std::string connectionDetails_;
  const bool persistent_;
  pqxx::connection* connection_;
};

#endif // STATICBASEDRIVER_H
