#include "EventNewSnapshotRequest.h"
#include <Controller/Controller.h>

namespace SimCity
{
namespace Controller
{
namespace Events
{

void EventNewSnapshotRequest::accept(Controller& visitor)
{
  visitor.visit(*this);
}

}//namespace Events
}//namespace Controller
}//namespace SimCity

