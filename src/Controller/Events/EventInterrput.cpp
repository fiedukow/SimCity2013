#include "EventInterrput.h"
#include <Controller/Controller.h>

namespace SimCity
{
namespace Controller
{
namespace Events
{

void EventInterrupt::accept(Controller& visitor)
{
  visitor.visit(*this);
}

}//namespace Events
}//namespace Controller
}//namespace SimCity

