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

Model::MapPtr QtUnspaghetti::getMapSnapshot()
{
  return currentMapPtr_;
}

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

void QtUnspaghetti::requestNewMapSnapshot()
{
  eventQueue_.push(EventBasePtr(new EventNewMapRequest()));
}

void QtUnspaghetti::emitUpdateMap(const Model::MapPtr map)
{
  currentMapPtr_ = map;
  emit updateMap();
}

}//namespace Controller
}//namespace SimCity

