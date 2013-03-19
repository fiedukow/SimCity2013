#include "Object.h"

namespace SimCity
{
namespace Model
{
namespace Objects
{

Object::Object()
{}

Object::~Object()
{}

PlacedObject::PlacedObject(const ObjectPtr& obj,
                           const Physics::Position& pos,
                           const Physics::Velocity& v)
  : obj(obj), pos(pos), v(v)
{}

ObjectPtr PlacedObject::getObjectPtr() const
{
  return obj;
}

Physics::Position PlacedObject::getPosition() const
{
  return pos;
}

Physics::Velocity PlacedObject::getVelocity() const
{
  return v;
}

void PlacedObject::dtMove(const Physics::TimeDuration& dt)
{
  //FIXME Only World should be able to call this.
  dtUpdatePosition(dt);
  dtUpdateVelocity(dt);
}

SnapshotPtr PlacedObject::getSnapshot() const
{
  return obj->getSnapshot(*this);
}

void PlacedObject::dtUpdatePosition(const Physics::TimeDuration& dt)
{
  Physics::Acceleration acc = obj->getCurrentForce() / obj->getCurrentMass();
  Physics::Shift shift = Physics::Shift(acc, dt)
                       + Physics::Shift(v, dt);
  pos = pos + shift;
}

void PlacedObject::dtUpdateVelocity(const Physics::TimeDuration& dt)
{
  Physics::Acceleration acc = obj->getCurrentForce() / obj->getCurrentMass();
  v = v + Physics::Velocity(acc*dt);
}

}//namespace Objects
}//namespace SimCity
}//namespace Model
