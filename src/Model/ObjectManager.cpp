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
{}

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
    StreetNodePtr endNode = (startDirection == Car::FS
                               ? startStreet->second
                               : startStreet->first);
    Physics::Position startPos(Physics::GeoCoords(startNode->lon.get(),
                                                  startNode->lat.get()));
    Physics::Position endPos(Physics::GeoCoords(endNode->lon.get(),
                                                endNode->lat.get()));

    bool isQuick = (rand()%10 == 0);

    double randTime = 5.0 + (rand()%100)/10.0;
    randTime /= 3.0;
    if(isQuick)
      randTime /= 2.0;

    Physics::Velocity startV((endPos-startPos)/Physics::TimeDuration(randTime));

    LiveObjectPtr newObject(new Car(map,
                                    startPos,
                                    startV,
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

