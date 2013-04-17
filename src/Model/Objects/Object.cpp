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

PlacedObject::PlacedObject(const Physics::Position& pos,
                           const Physics::Velocity& v)
  : pos(pos), v(v)
{}

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

void PlacedObject::dtUpdatePosition(const Physics::TimeDuration& dt)
{
  Physics::Acceleration acc = getCurrentForce() / getCurrentMass();
  Physics::Shift shift = Physics::Shift(acc, dt)
                       + Physics::Shift(v, dt);
  pos = pos + shift;
}

void PlacedObject::dtUpdateVelocity(const Physics::TimeDuration& dt)
{
  Physics::Acceleration acc = getCurrentForce() / getCurrentMass();
  v = v + Physics::Velocity(acc*dt);
}

}//namespace Objects
}//namespace SimCity
}//namespace Model
