#include "Timer.h"

namespace SimCity
{
namespace Model
{

Timer::Timer(time_t startTime)
  : time_(startTime),
    currentMs_(0)
{}

void Timer::timePassed(uint ms)
{
  currentMs_ += ms;
  while(currentMs_ > 1000)
  {
    ++time_;
    currentMs_ -= 1000; //it is ok if ms is not to big
  }
}

time_t Timer::getDBTime() const
{
  return time_;
}

}//namespace SimCity
}//namespace Model

