#include "QtUnspaghetti.h"
#include <Controller/Events/AllEvents.h>
namespace SimCity
{
namespace Controller
{
using namespace Events;

QtUnspaghetti::QtUnspaghetti(EventQueue& eventQueue)
  : eventQueue_(eventQueue)
{}

QtUnspaghetti::~QtUnspaghetti()
{}

void QtUnspaghetti::start()
{
  eventQueue_.push(EventBasePtr(new EventStart()));
}

void QtUnspaghetti::stop()
{
  eventQueue_.push(EventBasePtr(new EventStop()));
}

void QtUnspaghetti::pause()
{
  eventQueue_.push(EventBasePtr(new EventPause()));
}

void QtUnspaghetti::emitUpdateMap(const Model::Map* map)
{
  emit updateMap(map);
}

}//namespace Controller
}//namespace SimCity

