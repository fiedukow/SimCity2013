#include "World.h"
#include <Common/GlobalLogger.h>
#include <Model/StaticBaseDriver.h>
#include <sstream>

namespace SimCity
{
namespace Model
{

World::World(const std::string& dbName,
             const std::string& dbUser,
             const std::string& dbPassword)
  : map_(readMapFromDB(dbName, dbUser, dbPassword))
{
}

World::~World()
{
}

void World::timePassed(uint ms)
{
  std::stringstream ss;
  ss << "moving forward by " << ms << "ms.";
  Common::globLog("NOT", "World", ss.str());
  return;
}

Map World::readMapFromDB(const std::string& dbName,
                         const std::string& dbUser,
                         const std::string& dbPassword)
{
  StaticBaseDriver dbDriver(std::string("dbname=" + dbName +
                                        " user=" + dbUser +
                                        " password=" + dbPassword).c_str(),
                            true);
  return dbDriver.getMap();
}

}//namespace Model
}//namespace SimCity

