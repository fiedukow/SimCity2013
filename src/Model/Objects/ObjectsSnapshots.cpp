#include "ObjectsSnapshots.h"

namespace SimCity
{
namespace Model
{
namespace Objects
{

CarSnapshot::CarSnapshot(const Car& object)
  : Snapshot(object),
    isMad_(object.isMad())
{}

CarSnapshot::~CarSnapshot()
{}

bool CarSnapshot::isMad() const
{
  return isMad_;
}

void CarSnapshot::accept(SnapshotVisitor& visitor)
{
  visitor.visit(*this);
}

/******************************************************************************/
/******************************************************************************/

PedestrianSnapshot::PedestrianSnapshot(const Pedestrian& object)
  : Snapshot(object),
    isMad_(object.isMad())
{}

PedestrianSnapshot::~PedestrianSnapshot()
{}

bool PedestrianSnapshot::isMad() const
{
  return isMad_;
}

void PedestrianSnapshot::accept(SnapshotVisitor& visitor)
{
  visitor.visit(*this);
}

/******************************************************************************/
/******************************************************************************/

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

