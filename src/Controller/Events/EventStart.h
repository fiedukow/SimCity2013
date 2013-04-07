#ifndef EVENTSTART_H
#define EVENTSTART_H
#include <Controller/Events/EventBase.h>

namespace SimCity
{
namespace Controller
{
namespace Events
{

class EventStart : public EventBase
{
public:
  void accept(Controller& visitor);
};

}//namespace Events
}//namespace Controller
}//namespace SimCity

#endif // EVENTBASE_H
