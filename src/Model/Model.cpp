#include "Model.h"
#include <boost/thread/thread.hpp>
#include <Common/GlobalLogger.h>

namespace SimCity
{
namespace Model
{

Model::Model()
  : lastTickTime(MClock::local_time()),
    minTimerDelay(200),
    simulationSpeed(2.0),
    pollingPeriod(50),
    stopThreads_(false)
{
}

void Model::operator()()
{
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
    std::stringstream ss;
    ss << "Passed " << time.total_milliseconds();
    GlobalLogger::logger().log("NOT", "Model", ss.str());
    //TODO timePassed
  }
}

void Model::stopAllThreads()
{
  stopThreads_ = true;
}

}//namespace SimCity
}//namespace Model
