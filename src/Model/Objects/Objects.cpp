#include "Objects.h"
#include <Common/GlobalLogger.h>
#include <Model/Objects/ObjectsSnapshots.h>

namespace SimCity
{
namespace Model
{
namespace Objects
{

SnapshotPtr PowerBall::getSnapshot(const PlacedObject& place) const
{
  return SnapshotPtr(new PowerBallSnapshot(place));
}

Physics::Mass PowerBall::getCurrentMass() const
{
  return Physics::Mass(1.0);
}

Physics::Force PowerBall::getCurrentForce() const
{
  return Physics::Force(Physics::Vector3(1.0, 0.0, 0.0));
}

}//namesapce Objects
}//namespace SimCity
}//namespace Model

