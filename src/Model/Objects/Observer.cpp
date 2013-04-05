#include "Observer.h"
#include <Model/DBDataStructures.h>

namespace SimCity
{
namespace Model
{
namespace Objects
{

Observer::Observer(const Map& map)
  : map_(map)
{
}

Observer::~Observer()
{}

}//namesapce Objects
}//namespace SimCity
}//namespace Model
