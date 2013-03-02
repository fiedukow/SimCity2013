#include "Model.h"
#include <boost/thread/thread.hpp>

namespace SimCity
{
namespace Model
{

Model::Model()
  : lastTickTime(MClock::local_time()),
    minTimerDelay(100),
    simulationSpeed(0.1),
    pollingPeriod(50)
{
}

void Model::operator()()
{
  while(true)
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
    std::cout << "Passed " << time.total_milliseconds() << std::endl;
    //TODO timePassed
  }
}

}//namespace SimCity
}//namespace Model
