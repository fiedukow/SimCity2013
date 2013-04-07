#include "Model.h"
#include <boost/thread/thread.hpp>
#include <Common/GlobalLogger.h>
#include <Model/Exceptions.h>

namespace SimCity
{
namespace Model
{

Model::Model()
  : minTimerDelay(100),
    simulationSpeed(1.0),
    pollingPeriod(20),
    stopThreads_(false),
    paused_(false),
    threadRunning_(false),
    thread_(NULL)
{
}

void Model::registerNewStateObserver(Common::NewStateObserver* obs)
{
  newStateObservers_.push_back(obs);
}

void Model::unregisterNewStateObserver(Common::NewStateObserver* obs)
{
  newStateObservers_.remove(obs);
}

void Model::notifyNewStateObservers()
{
  for(Common::NewStateObserver* observer : newStateObservers_)
    observer->notifyNewState();
}

void Model::start()
{
  paused_ = false;
  pauseMutex_.unlock();

  if(!thread_)
  {
    thread_ = new boost::thread(boost::ref(*this));
    stopThreads_ = false;
  }
}

void Model::stop()
{
  if(!thread_)
    return;

  start(); //Unpause if it was paused
  stopThreads_ = true;
  thread_->join();
  delete thread_;
  thread_ = NULL;
}

void Model::pause()
{
  if(!thread_)
    return;

  if(pauseMutex_.try_lock())
    paused_ = true;
}

void Model::operator()()
{
  threadRunning_ = true;
  ptime lastTickTime = MClock::local_time();
  while(!stopThreads_)
  {
    std::cout << &pauseMutex_ << "lck loop" << std::endl;
    ptime current;
    Time::time_duration durr;
    while(durr.total_milliseconds() < minTimerDelay)
    {
      current = MClock::local_time();
      durr = (current - lastTickTime);
      boost::this_thread::sleep(Time::milliseconds(pollingPeriod));
    }

    lastTickTime = current;
    Time::time_duration time = Time::milliseconds(durr.total_milliseconds()
                                                  * simulationSpeed);
    int passed = time.total_milliseconds();

    std::stringstream ss;
    ss << "Passed " << passed;
    Common::globLog("NOT", "Model", ss.str());

    /**
     * Loop through all simulation parts.and move them
     */
    for(SimulationPartPtr& simPart : simParts_)
      simPart->timePassed(passed);

    if(paused_)
    {
      Common::GlobalLogger::logger().log("DBG", "Model", "PAUSED");
      boost::mutex::scoped_lock lock(pauseMutex_);
    }
  }
}

void Model::addSimulationPart(SimulationPartPtr newSimPart)
{
  if(threadRunning_)
    throw GeneralException("Trying to add simulation part while simulation has"
                           " already started.");
  simParts_.push_back(newSimPart);
}

}//namespace SimCity
}//namespace Model
