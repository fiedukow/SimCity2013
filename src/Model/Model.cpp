#include "Model.h"
#include <boost/thread/thread.hpp>
#include <Common/GlobalLogger.h>
#include <Model/Exceptions.h>
#include <Model/World.h>
#include <Model/ObjectManager.h>

namespace SimCity
{
namespace Model
{

Model::Model(const std::string& dbName,
             const std::string& dbUserName,
             const std::string& dbPassword)
  : minTimerDelay_(32),
    simulationSpeed_(1.00),
    pollingPeriod_(0),
    stopThreads_(false),
    paused_(false),
    threadRunning_(false),
    world_(NULL),
    thread_(NULL),
    dbName_(dbName),
    dbUser_(dbUserName),
    dbPassword_(dbPassword),
    objectsLimit_(10)
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
    newSimulation();
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
  threadRunning_ = false;
}

void Model::pause()
{
  if(!thread_)
    return;

  if(pauseMutex_.try_lock())
    paused_ = true;
}

void Model::setSimulationSpeed(double speed)
{
  simulationSpeed_ = speed;
}

void Model::setCarLimit(uint limit)
{
  if(objectManager_.get() == NULL)
    return; //TODO it should be saved for future usages

  objectManager_->setCarLimit(limit);
}

void Model::setPedestrianLimit(uint limit)
{
  if(objectManager_.get() == NULL)
    return; //TODO it should be saved for future usages

  objectManager_->setPedestrianLimit(limit);
}

MapPtr Model::getMapSnapshot()
{
  if(world_.get() == NULL)
    return NULL;
  return world_->getMapSnapshot();
}

Objects::Snapshots Model::getObjectSnapshots()
{
  if(world_.get() == NULL)
    return Objects::Snapshots();
  return world_->getObjectSnapshots();
}

void Model::operator()()
{
  threadRunning_ = true;
  ptime lastTickTime = MClock::local_time();
  while(!stopThreads_)
  {
    ptime current;
    Time::time_duration durr;
    while(durr.total_milliseconds() < minTimerDelay_)
    {
      current = MClock::local_time();
      durr = (current - lastTickTime);
      boost::this_thread::sleep(Time::milliseconds(pollingPeriod_));
    }

    lastTickTime = current;
    int passed = durr.total_milliseconds()*simulationSpeed_;

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
      lastTickTime = MClock::local_time();
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


void Model::newSimulation()
{
  try
  {
    world_ = WorldPtr(new World(dbName_, dbUser_, dbPassword_));
    objectManager_ = ObjectManagerPtr(new ObjectManager(world_,
                                                        dbName_,
                                                        dbUser_,
                                                        dbPassword_,
                                                        objectsLimit_));
    addSimulationPart(std::dynamic_pointer_cast<SimulationPart>(world_));
    addSimulationPart(std::dynamic_pointer_cast<SimulationPart>(objectManager_));
  }
  catch(GeneralException& e)
  {
    std::cout << "An unhandable problem occured while running application"
              << std::endl;
    std::cout << "Application will be killed as there is nothing we can do."
              << std::endl;
    std::cout << "Here are some details: " << std::endl;
    std::cout << e.what();
    std::cout << "\nHTH." << std::endl;
    exit(1);
  }
}

}//namespace SimCity
}//namespace Model
