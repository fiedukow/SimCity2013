#ifndef STATICBASEDRIVER_H
#define STATICBASEDRIVER_H

#include <string>
#include <vector>

#include <pqxx/pqxx>

#include <Model/DBDataStructures.h>

namespace SimCity
{
namespace Model
{

/**
 * @brief Class used to communicate with postgresql database
 *
 * This class implements connection to posgresql and some basic
 * db operation connected with this application.
 * It allows to get any information are needed from SimCity official
 * db structure.
 *
 * It uses pqxx library to communicate with postgresql
 *
 * @author Andrzej 'fiedukow' Fiedukowicz
 */
class StaticBaseDriver
{
public:
  StaticBaseDriver(const char* connectionDetails = "",
                   bool persistent = true);
  ~StaticBaseDriver();
  std::vector<StreetNode> getStreetNodes();
  Map getMap();

private:
  /**
   * @brief ensures that class instantion has established connection to db
   *
   * Connect to RDBMS if connection isn't already established
   * throws an exception if failed.
   *
   * @returns bool - true if connection was established now
   *                 or false if it was already created earlier.
   * @throw GeneralException - if an exception occured while
   *                           trying to connect to RDBMS
   */
  bool ensureDBConnection();
  bool disconnectIfNecessary();
  void connect();
  void disconnect();

private:
  const std::string connectionDetails_;
  const bool persistent_;
  pqxx::connection* connection_;
};

}//namespace Model
}//namespace SimCity

#endif // STATICBASEDRIVER_H
