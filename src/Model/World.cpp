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
                      Physics::Position(20906.3, 5834.48, 0),
                      Physics::Velocity(-5.0, 1.0, 1.0));
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

  /**
   * Create snapshot of current state
   */
//  Snapshots objectsSnapshot;
//  for(PlacedObject& placedObject : objects_)
//    objectsSnapshot.push_back(placedObject.getSnapshot());

  /**
   * Loop through all observer and tell them whats going on
   */
  //TODO

  /**
   * Loop through all object and move them using force and mass they're providin
   */
  for(PlacedObject& placedObject : objects_)
  {
    placedObject.dtMove(dt);
    std::cout << "Position " << placedObject.getPosition().x << std::endl;
  }

  return;
}

MapPtr World::getMapSnapshot()
{
  return map_;
}

Snapshots World::getObjectSnapshots()
{
  Snapshots result;
  for(PlacedObject& placedObject : objects_)
    result.push_back(placedObject.getSnapshot());
  return result;
}


MapPtr World::readMapFromDB(const std::string& dbName,
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

