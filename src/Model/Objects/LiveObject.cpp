#include "LiveObject.h"

namespace SimCity
{
namespace Model
{
namespace Objects
{

LiveObject::LiveObject(const MapPtr map,
                       const Physics::Position& pos,
                       const Physics::Velocity& v)
  : Observer(map),
    PlacedObject(pos, v)
{}

LiveObject::~LiveObject()
{}

}//namespace Objects
}//namespace Model
}//namespace SimCity
