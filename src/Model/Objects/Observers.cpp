#include "Observers.h"
#include <Model/World.h>
#include <Common/GlobalLogger.h>
#include <Model/Objects/ObjectsSnapshots.h>

#include <iostream>

namespace SimCity
{
namespace Model
{
namespace Objects
{

RoadUserObserver::RoadUserObserver(const MapPtr& map)
  : Observer(map)
{}

RoadUserObserver::~RoadUserObserver()
{}

void RoadUserObserver::visit(CarSnapshot&)
{}

void RoadUserObserver::visit(PedestrianSnapshot&)
{}

void RoadUserObserver::visit(SensorSnapshot&)
{}

void RoadUserObserver::accept(World& w)
{
  w.visit(*this);
}

SensorObserver::SensorObserver(const MapPtr& map)
  : Observer(map)
{}

SensorObserver::~SensorObserver()
{}

void SensorObserver::accept(World& w)
{
  w.visit(*this);
}

}//namespace Objects
}//namespace Model
}//namespace SimCity
