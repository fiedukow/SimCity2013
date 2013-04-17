#ifndef EVENTSETSIMULATIONSPEED_H
#define EVENTSETSIMULATIONSPEED_H
#include <Controller/Events/EventBase.h>

namespace SimCity
{
namespace Controller
{
namespace Events
{

class EventSetSimulationSpeed : public EventBase
{
public:
  EventSetSimulationSpeed(double speed);
  void accept(Controller& visitor);
  double getSpeed() const;

private:
  const double speed_;
};

}//namespace Events
}//namespace Controller
}//namespace SimCity

#endif // EVENTBASE_H
