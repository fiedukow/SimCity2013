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
  : PlacedObject(pos, v),
    Observer(map)
{}

LiveObject::~LiveObject()
{}

}//namespace Objects
}//namespace Model
}//namespace SimCity
