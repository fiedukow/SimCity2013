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

CarObserver::CarObserver(const MapPtr& map)
  : Observer(map)
{}

CarObserver::~CarObserver()
{}

void CarObserver::visit(CarSnapshot&)
{}

void CarObserver::visit(SensorSnapshot&)
{}

void CarObserver::accept(World& w)
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
