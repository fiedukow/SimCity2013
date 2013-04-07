#include "EventStart.h"
#include <Controller/Controller.h>

namespace SimCity
{
namespace Controller
{
namespace Events
{

void EventStart::accept(Controller& visitor)
{
  visitor.visit(*this);
}

}//namespace Events
}//namespace Controller
}//namespace SimCity

