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

Snapshot::~Snapshot()
{}

SnapshotVisitor::~SnapshotVisitor()
{}

}//namespace Objects
}//namespace SimCity
}//namespace Model
