#ifndef OBJECT_H
#define OBJECT_H
#include <Model/Physics/NewtonsDynamics.h>
#include <Model/Physics/Positioning.h>
#include <memory>

namespace SimCity
{
namespace Model
{
namespace Objects
{

class Snapshot;
class PlacedObject;
typedef std::shared_ptr<Snapshot> SnapshotPtr;

class Object
{
public:
  Object();
  virtual ~Object();

  virtual SnapshotPtr getSnapshot(const PlacedObject&) const = 0;
  virtual Physics::Mass getCurrentMass() const = 0;   //Argh...
                                                      //Heisenberg would kill me
                                                      // for this const here...
  virtual Physics::Force getCurrentForce() const = 0;
};

typedef std::shared_ptr<Object> ObjectPtr;

class PlacedObject
{
public:
  PlacedObject(const ObjectPtr& obj,
               const Physics::Position& pos,
               const Physics::Velocity& v);

  ObjectPtr getObjectPtr() const;
  Physics::Position getPosition() const;
  Physics::Velocity getVelocity() const;
  void dtMove(const Physics::TimeDuration& dt);

  SnapshotPtr getSnapshot() const;

private:
  void dtUpdatePosition(const Physics::TimeDuration& dt);
  void dtUpdateVelocity(const Physics::TimeDuration& dt);

private:
  ObjectPtr obj;
  Physics::Position pos;
  Physics::Velocity v;
};

typedef std::shared_ptr<PlacedObject> PlacedObjectPtr;

}//namespace Objects
}//namespace SimCity
}//namespace Model

#endif // OBJECT_H
