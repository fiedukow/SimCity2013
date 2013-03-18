#include "World.h"
#include <Common/GlobalLogger.h>
#include <Model/StaticBaseDriver.h>
#include <Model/Objects/Objects.h>
#include <Model/Objects/Object.h>
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
  PlacedObject myBall(ObjectPtr(new PowerBall()),
                      Physics::Position(0, 0, 0),
                      Physics::Velocity(0, 0, 0));
  objects_.push_back(myBall);
}

World::~World()
{
}

void World::timePassed(uint ms)
{
  std::stringstream ss;
  ss << "moving forward by " << ms << "ms.";
  Common::globLog("NOT", "World", ss.str());

  Physics::TimeDuration dt(ms/1000.0);

  for(PlacedObject& placedObject : objects_)
  {
    std::stringstream ss;
    ss << "Moving the object from place ("
       << placedObject.getPosition().x << ", "
       << placedObject.getPosition().y << ", "
       << placedObject.getPosition().z << ") ";

    placedObject.dtMove(dt);

    ss << "to place ("
       << placedObject.getPosition().x << ", "
       << placedObject.getPosition().y << ", "
       << placedObject.getPosition().z << ") ";
    Common::globLog("DBG", "World", ss.str());
  }
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

