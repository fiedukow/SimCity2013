#include "ObjectManager.h"
#include <Common/GlobalLogger.h>
#include <Model/World.h>
#include <Model/Objects/Objects.h>
#include <memory>

#include <Model/StaticBaseDriver.h>

namespace SimCity
{
namespace Model
{

ObjectManager::ObjectManager(WorldPtr world,
                             const std::string& dbName,
                             const std::string& dbUser,
                             const std::string& dbPassword,
                             uint limit)
  : world_(world),
    limit_(limit)
{
  StaticBaseDriver dbDriver(std::string("dbname=" + dbName +
                                        " user=" + dbUser +
                                        " password=" + dbPassword).c_str(),
                            true);

  Sensors sensors = dbDriver.getSensors();
  MapPtr map = world_->getMapSnapshot();

  for(SensorPtr sensor : sensors)
  {
    Physics::Position pos(Physics::GeoCoords(sensor->lon.get(),
                                             sensor->lat.get()));
    LiveObjectPtr newSensor(new RadiusSensor(sensor->sensorId,
                                             map,
                                             pos,
                                             360.0,
                                             sensor->range));
    world_->addObserver(std::dynamic_pointer_cast<Observer>(newSensor));
    world_->addPlacedObject(std::dynamic_pointer_cast<PlacedObject>(newSensor));
  }
}

ObjectManager::~ObjectManager()
{}

void ObjectManager::timePassed(uint/*ms*/)
{
  MapPtr map = world_->getMapSnapshot();
  while(objects_.size() < limit_)
  {
    std::stringstream ss;
    ss << "Adding new object: ";
    StreetPtr startStreet = map->edges[rand()%map->edges.size()];
    Car::Direction startDirection = rand()%2 ? Car::FS : Car::SF;
    StreetNodePtr startNode = (startDirection == Car::FS
                               ? startStreet->first
                               : startStreet->second);
    Physics::Position startPos(Physics::GeoCoords(startNode->lon.get(),
                                                  startNode->lat.get()));

    bool isQuick = (rand()%10 == 0);

    LiveObjectPtr newObject(new Car(map,
                                    startPos,
                                    startStreet,
                                    startDirection,
                                    isQuick));
    objects_.push_back(newObject);
    world_->addObserver(std::dynamic_pointer_cast<Observer>(newObject));
    world_->addPlacedObject(std::dynamic_pointer_cast<PlacedObject>(newObject));
    Common::globLog("NOT", "ObjMgr", ss.str());
  }

  while(objects_.size() > limit_)
  {
    world_->removeObserver(objects_.front());
    world_->removePlacedObject(objects_.front());
    objects_.pop_front();
  }

  return;
}

void ObjectManager::setCarLimit(uint limit)
{
  limit_ = limit;
}

}//namespace SimCity
}//namespace Model

