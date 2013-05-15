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
                             uint limit,
                             uint pedestrianLimit)
  : world_(world),
    limit_(limit),
    pedestrianLimit_(pedestrianLimit)
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
    bool isQuick = (rand()%10 == 0);
    LiveObjectPtr newObject(new Car(map, isQuick));

    objects_.push_back(newObject);
    world_->addObserver(std::dynamic_pointer_cast<Observer>(newObject));
    world_->addPlacedObject(std::dynamic_pointer_cast<PlacedObject>(newObject));
  }

  while(objects_.size() > limit_)
  {
    world_->removeObserver(objects_.front());
    world_->removePlacedObject(objects_.front());
    objects_.pop_front();
  }

  while(pedestrians_.size() < pedestrianLimit_)
  {
    bool isQuick = (rand()%10 == 0);
    LiveObjectPtr newObject(new Pedestrian(map, isQuick));

    pedestrians_.push_back(newObject);
    world_->addObserver(std::dynamic_pointer_cast<Observer>(newObject));
    world_->addPlacedObject(std::dynamic_pointer_cast<PlacedObject>(newObject));
  }

  while(pedestrians_.size() > pedestrianLimit_)
  {
    world_->removeObserver(pedestrians_.front());
    world_->removePlacedObject(pedestrians_.front());
    pedestrians_.pop_front();
  }

  return;
}

void ObjectManager::setCarLimit(uint limit)
{
  limit_ = limit;
}

void ObjectManager::setPedestrianLimit(uint limit)
{
  pedestrianLimit_ = limit;
}

}//namespace SimCity
}//namespace Model

