#include "Objects.h"
#include <Common/GlobalLogger.h>
#include <Model/Objects/ObjectsSnapshots.h>

namespace SimCity
{
namespace Model
{
namespace Objects
{

Car::Car(const MapPtr map,
         const Physics::Position& pos,
         const Physics::Velocity& v,
         const StreetPtr street,
         const Direction direction)
  : Observer(map),
    LiveObject(map, pos, v),
    CarObserver(map),
    street_(street),
    direction_(direction)
{}

Car::~Car()
{}

void Car::timePassed(uint)
{
  //TODO change street when in place?
}

SnapshotPtr Car::getSnapshot() const
{
  return SnapshotPtr(new CarSnapshot(*this));
}

Physics::Mass Car::getCurrentMass() const
{
  return Physics::Mass(1000.0);
}

Physics::Force Car::getCurrentForce() const
{
  return Physics::Force(Physics::Vector3(0.0, 0.0, 0.0));
}

}//namesapce Objects
}//namespace SimCity
}//namespace Model

