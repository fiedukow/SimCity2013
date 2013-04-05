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
typedef std::vector<SnapshotPtr> ObjectSnapshots;

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

class PowerBallSnapshot;

class SnapshotVisitor
{
public:
  virtual ~SnapshotVisitor();

  virtual void visit(PowerBallSnapshot& powerBall) = 0;
};

}//namesapce Objects
}//namespace SimCity
}//namespace Model

#endif // OBJECTSNAPSHOT_H
