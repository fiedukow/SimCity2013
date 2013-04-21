#include "ObjectsSnapshots.h"

namespace SimCity
{
namespace Model
{
namespace Objects
{

CarSnapshot::CarSnapshot(const PlacedObject& object)
  : Snapshot(object)
{}

CarSnapshot::~CarSnapshot()
{}

void CarSnapshot::accept(SnapshotVisitor& visitor)
{
  visitor.visit(*this);
}

SensorSnapshot::SensorSnapshot(const RadiusSensor& object)
  : Snapshot(object),
    range_(object.getRange())
{}

SensorSnapshot::~SensorSnapshot()
{}

double SensorSnapshot::getRange() const
{
  return range_;
}

void SensorSnapshot::accept(SnapshotVisitor& visitor)
{
  visitor.visit(*this);
}

}//namesapce Objects
}//namespace SimCity
}//namespace Model

