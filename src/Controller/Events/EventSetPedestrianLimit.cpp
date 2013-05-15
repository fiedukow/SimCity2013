#include "EventSetPedestrianLimit.h"
#include <Controller/Controller.h>

namespace SimCity
{
namespace Controller
{
namespace Events
{

EventSetPedestrianLimit::EventSetPedestrianLimit(int limit)
  : limit_(limit)
{}

uint EventSetPedestrianLimit::getLimit() const
{
  return limit_;
}

void EventSetPedestrianLimit::accept(Controller& visitor)
{
  visitor.visit(*this);
}

}//namespace Events
}//namespace Controller
}//namespace SimCity

