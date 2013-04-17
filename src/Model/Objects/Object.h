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

  virtual Physics::Mass getCurrentMass() const = 0;   //Argh...
                                                      //Heisenberg would kill me
                                                      // for this const here...
  virtual Physics::Force getCurrentForce() const = 0;
};

typedef std::shared_ptr<Object> ObjectPtr;

class PlacedObject : public Object
{
public:
  PlacedObject(const Physics::Position& pos,
               const Physics::Velocity& v);

  void timePassed(uint ms);

  virtual Physics::Position getPosition() const;
  virtual Physics::Velocity getVelocity() const;
  void dtMove(const Physics::TimeDuration& dt);

  virtual SnapshotPtr getSnapshot() const = 0;

private:
  void dtUpdatePosition(const Physics::TimeDuration& dt);
  void dtUpdateVelocity(const Physics::TimeDuration& dt);

private:
  Physics::Position pos;
  Physics::Velocity v;
};

typedef std::shared_ptr<PlacedObject> PlacedObjectPtr;

}//namespace Objects
}//namespace SimCity
}//namespace Model

#endif // OBJECT_H
