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
         const Physics::Velocity& v)
  : LiveObject(map, pos, v)
{}

Car::~Car()
{}

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
  return Physics::Force(Physics::Vector3(1.0, 0.0, 0.0));
}

}//namesapce Objects
}//namespace SimCity
}//namespace Model

