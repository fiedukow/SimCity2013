#ifndef EVENTNEWSNAPSHOTREQUEST_H
#define EVENTNEWSNAPSHOTREQUEST_H
#include <Controller/Events/EventBase.h>

namespace SimCity
{
namespace Controller
{
namespace Events
{

class EventNewSnapshotRequest : public EventBase
{
public:
  void accept(Controller& visitor);
};

}//namespace Events
}//namespace Controller
}//namespace SimCity

#endif // EVENTBASE_H
