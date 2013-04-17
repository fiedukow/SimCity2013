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
  updateObjectSnapshots();

  /**
   * Loop through all observer and tell them whats going on
   */
  for(ObserverPtr& observer : observers_)
  {
    observer->accept(*this);
    observer->timePassed(ms);
  }

  /**
   * Loop through all object and move them using force and mass they're providin
   */
  for(PlacedObjectPtr& placedObject : objects_)
  {
    placedObject->dtMove(dt);
    std::cout << "Position " << placedObject->getPosition().x << std::endl;
  }

  return;
}

MapPtr World::getMapSnapshot()
{
  return map_;
}

Snapshots World::getObjectSnapshots()
{
  boost::mutex::scoped_lock lock(snapshotMutex_);
  return snapshot_;
}

void World::updateObjectSnapshots()
{
  boost::mutex::scoped_lock lock(snapshotMutex_);
  snapshot_.clear();
  for(PlacedObjectPtr& placedObject : objects_)
    snapshot_.push_back(placedObject->getSnapshot());
}

void World::visit(CarObserver& car)
{
  car.provideObjects(snapshot_);
}

void World::addPlacedObject(PlacedObjectPtr obj)
{
  objects_.push_back(obj);
}

void World::removePlacedObject(PlacedObjectPtr obj)
{
  objects_.remove(obj);
}

void World::addObserver(ObserverPtr obs)
{
  observers_.push_back(obs);
}

void World::removeObserver(ObserverPtr obs)
{
  observers_.remove(obs);
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

