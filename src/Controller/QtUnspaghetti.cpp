#include "QtUnspaghetti.h"
#include <Controller/Events/AllEvents.h>
#include <Model/Objects/ObjectsSnapshots.h>
#include <QMutexLocker>

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
  QMutexLocker lock(&oneWayLock_);
  return currentMapPtr_;
}

Model::Objects::Snapshots QtUnspaghetti::getSnapshots()
{
  QMutexLocker lock(&oneWayLock_);
  return currentSnapshot_;
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

void QtUnspaghetti::requestSnapshot()
{
  eventQueue_.push(EventBasePtr(new EventNewSnapshotRequest()));
}

void QtUnspaghetti::setSimulationSpeed(double speed)
{
  eventQueue_.push(EventBasePtr(new EventSetSimulationSpeed(speed)));
}

void QtUnspaghetti::emitUpdateMap(const Model::MapPtr map)
{
  oneWayLock_.lock();
  currentMapPtr_ = map;
  oneWayLock_.unlock();
  emit updateMap();
}

void QtUnspaghetti::emitUpdateSnapshot(const Model::Objects::Snapshots& snaps)
{
  oneWayLock_.lock();
  currentSnapshot_ = snaps;
  oneWayLock_.unlock();
  emit updateState();
}

}//namespace Controller
}//namespace SimCity

