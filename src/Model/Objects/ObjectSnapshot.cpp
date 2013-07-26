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
    v(base.getVelocity()),
    id(&base)
{}

Physics::Position Snapshot::getPosition() const
{
  return pos;
}
Physics::Velocity Snapshot::getVelocity() const
{
  return v;
}
unsigned int Snapshot::getId() const
{
  return static_cast<unsigned int>(id);
}

Snapshot::~Snapshot()
{}

SnapshotVisitor::~SnapshotVisitor()
{}

}//namespace Objects
}//namespace SimCity
}//namespace Model
