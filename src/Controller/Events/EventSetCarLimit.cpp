#include "EventSetCarLimit.h"
#include <Controller/Controller.h>

namespace SimCity
{
namespace Controller
{
namespace Events
{

EventSetCarLimit::EventSetCarLimit(uint limit)
  : limit_(limit)
{}

void EventSetCarLimit::accept(Controller& visitor)
{
  visitor.visit(*this);
}

uint EventSetCarLimit::getLimit() const
{
  return limit_;
}

}//namespace Events
}//namespace Controller
}//namespace SimCity

