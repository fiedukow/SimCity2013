#include "ObjectsSnapshots.h"

namespace SimCity
{
namespace Model
{
namespace Objects
{

PowerBallSnapshot::PowerBallSnapshot(const PlacedObject& object)
  : Snapshot(object)
{}

PowerBallSnapshot::~PowerBallSnapshot()
{}

void PowerBallSnapshot::accept(SnapshotVisitor& visitor)
{
  visitor.visit(*this);
}

}//namesapce Objects
}//namespace SimCity
}//namespace Model

