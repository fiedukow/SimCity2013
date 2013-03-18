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

void PlacedObject::dtMove() const
{
  dtUpdatePosition();
  dtUpdateSpeed();
}

void PlacedObject::dtUpdatePosition() const
{
  //FIXME implement this
  //shift = (at^2)/2
  //pos = pos + shift
}

void PlacedObject::dtUpdateVelocity() const
{
  //FIXME implement this
  //v = v + at
}

}//namespace Objects
}//namespace SimCity
}//namespace Model
