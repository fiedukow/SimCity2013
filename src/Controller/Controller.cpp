#include "Controller.h"
#include <Common/GlobalLogger.h>
#include <Controller/Events/EventInterrput.h>

#include <boost/thread.hpp>

namespace SimCity
{
namespace Controller
{

Controller::Controller(QtUnspaghetti& qtControll,
                       Events::EventQueue& eventQueue,
                       Model::Model& model)
  : qtControll_(qtControll),
    eventQueue_(eventQueue),
    model_(model),
    thread_(NULL)
{
  startThread();
}

Controller::~Controller()
{
  stopThread();
}

void Controller::operator()()
{
  while(!stopThread_)
  {
    EventBasePtr event;
    eventQueue_.pop(event);
    event->accept(*this);
  }
}

void Controller::notifyNewState()
{
  //FIXME implement this
}

void Controller::visit(EventStop&)
{
  model_.stop();
}

void Controller::visit(EventStart&)
{
  model_.start();
}

void Controller::visit(EventPause&)
{
  model_.pause();
}

void Controller::visit(EventInterrupt&)
{
  //noop
}

void Controller::visit(EventNewMapRequest&)
{
  qtControll_.emitUpdateMap(model_.getMapSnapshot());
}

void Controller::visit(EventNewSnapshotRequest&)
{
  qtControll_.emitUpdateSnapshot(model_.getObjectSnapshots());
}

void Controller::visit(EventSetSimulationSpeed& event)
{
  model_.setSimulationSpeed(event.getSpeed());
}

void Controller::visit(EventSetCarLimit& event)
{
  model_.setCarLimit(event.getLimit());
}

void Controller::startThread()
{
  if(thread_)
    return;

  stopThread_ = false;
  thread_ = new boost::thread(boost::ref(*this));
}

void Controller::stopThread()
{
  if(!thread_)
    return;

  stopThread_ = true;
  eventQueue_.push(Events::EventBasePtr(new Events::EventInterrupt()));
  thread_->join();
  delete thread_;
  thread_ = NULL;
}

}//namespace Controller
}//namespace SimCity

