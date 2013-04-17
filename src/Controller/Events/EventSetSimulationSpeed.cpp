#include "EventSetSimulationSpeed.h"
#include <Controller/Controller.h>

namespace SimCity
{
namespace Controller
{
namespace Events
{

EventSetSimulationSpeed::EventSetSimulationSpeed(double speed)
  : speed_(speed)
{}

void EventSetSimulationSpeed::accept(Controller& visitor)
{
  visitor.visit(*this);
}

double EventSetSimulationSpeed::getSpeed() const
{
  return speed_;
}

}//namespace Events
}//namespace Controller
}//namespace SimCity

