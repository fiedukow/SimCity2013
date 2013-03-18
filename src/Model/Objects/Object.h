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

class Object
{
public:
  Object();
  virtual ~Object();

  virtual void getSnapshot() const = 0; //TODO it is no void returning
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
  void dtMove(Physics::TimeDuration dt);

private:
  void dtUpdatePosition();
  void dtUpdateVelocity();

private:
  ObjectPtr obj;
  Physics::Position pos;
  Physics::Velocity v;
};

}//namespace Objects
}//namespace SimCity
}//namespace Model

#endif // OBJECT_H
