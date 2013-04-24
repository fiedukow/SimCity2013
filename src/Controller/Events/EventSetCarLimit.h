#ifndef EVENTSETCARLIMIT_H
#define EVENTSETCARLIMIT_H
#include <Controller/Events/EventBase.h>

namespace SimCity
{
namespace Controller
{
namespace Events
{

class EventSetCarLimit : public EventBase
{
public:
  EventSetCarLimit(uint limit);
  void accept(Controller& visitor);
  uint getLimit() const;

private:
  const uint limit_;
};

}//namespace Events
}//namespace Controller
}//namespace SimCity

#endif // EVENTBASE_H
