#ifndef EVENTSETPEDESTRIANLIMIT_H
#define EVENTSETPEDESTRIANLIMIT_H
#include <Controller/Events/EventBase.h>

namespace SimCity
{
namespace Controller
{
namespace Events
{

class EventSetPedestrianLimit : public EventBase
{
public:
  EventSetPedestrianLimit(int limit);
  void accept(Controller& visitor);
  uint getLimit() const;

private:
  const uint limit_;
};

}//namespace Events
}//namespace Controller
}//namespace SimCity

#endif // EVENTBASE_H
