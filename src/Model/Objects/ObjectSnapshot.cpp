#include "ObjectSnapshot.h"
#include <Model/Objects/Object.h>

namespace SimCity
{
namespace Model
{
namespace Objects
{

Snapshot::Snapshot(const PlacedObject &base)
  : pos(base.getPosition()),
    v(base.getVelocity())
{}

Physics::Position Snapshot::getPosition() const
{
  return pos;
}
Physics::Velocity Snapshot::getVelocity() const
{
  return v;
}

Snapshot::~Snapshot()
{}

SnapshotVisitor::~SnapshotVisitor()
{}

}//namespace Objects
}//namespace SimCity
}//namespace Model
