#include "ObjectManager.h"
#include <Common/GlobalLogger.h>
#include <Model/World.h>
#include <Model/Objects/Objects.h>
#include <memory>

namespace SimCity
{
namespace Model
{

ObjectManager::ObjectManager(WorldPtr world, uint limit)
  : world_(world),
    limit_(limit)
{
  MapPtr map = world_->getMapSnapshot();
  for(StreetNodePtr& node : map->vertexes)
  {
    Physics::Position pos(Physics::GeoCoords(node->lon.get(),
                                             node->lat.get()));
    LiveObjectPtr newSensor(new Sensor(map, pos, 360.0, 40.0));
    world_->addObserver(std::dynamic_pointer_cast<Observer>(newSensor));
    world_->addPlacedObject(std::dynamic_pointer_cast<PlacedObject>(newSensor));
  }
}

ObjectManager::~ObjectManager()
{}

void ObjectManager::timePassed(uint ms)
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
  return;
}



}//namespace SimCity
}//namespace Model

