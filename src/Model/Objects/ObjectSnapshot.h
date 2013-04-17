#ifndef OBJECTSNAPSHOT_H
#define OBJECTSNAPSHOT_H

#include <memory>
#include <vector>
#include <Model/Physics/NewtonsDynamics.h>
#include <Model/Physics/Positioning.h>

namespace SimCity
{
namespace Model
{
namespace Objects
{

class Snapshot;
class SnapshotVisitor;
class PlacedObject;
typedef std::shared_ptr<Snapshot> SnapshotPtr;
typedef std::vector<SnapshotPtr> Snapshots;

class Snapshot
{
public:
  Snapshot(const PlacedObject& base);
  virtual ~Snapshot();

  virtual void accept(SnapshotVisitor&) = 0;

  Physics::Position getPosition() const;
  Physics::Velocity getVelocity() const;

private:
  Physics::Position pos;
  Physics::Velocity v;
};

class CarSnapshot;
class SensorSnapshot;

class SnapshotVisitor
{
public:
  virtual ~SnapshotVisitor();

  virtual void visit(CarSnapshot& car) = 0;
  virtual void visit(SensorSnapshot& sensor) = 0;
};

}//namesapce Objects
}//namespace SimCity
}//namespace Model

#endif // OBJECTSNAPSHOT_H
