#include "Observers.h"
#include <Model/World.h>

namespace SimCity
{
namespace Model
{
namespace Objects
{

CarObserver::CarObserver(const MapPtr& map)
  : Observer(map)
{}

CarObserver::~CarObserver()
{}

void CarObserver::visit(CarSnapshot&)
{}

void CarObserver::accept(World &w)
{
  w.visit(*this);
}

}//namespace Objects
}//namespace Model
}//namespace SimCity
