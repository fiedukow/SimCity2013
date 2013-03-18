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
    threadRunning_(false)
{
}

void Model::operator()()
{
  threadRunning_ = true;
  ptime lastTickTime = MClock::local_time();
  while(!stopThreads_)
  {
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
  }
}

void Model::addSimulationPart(SimulationPartPtr newSimPart)
{
  if(threadRunning_)
    throw GeneralException("Trying to add simulation part while simulation has"
                           " already started.");
  simParts_.push_back(newSimPart);
}

void Model::stopAllThreads()
{
  stopThreads_ = true;
}

}//namespace SimCity
}//namespace Model
