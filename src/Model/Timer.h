#ifndef TIMER_H
#define TIMER_H
#include <Model/SimulationPart.h>
#include <memory>

namespace SimCity
{
namespace Model
{

class Timer : public SimulationPart
{
public:
  Timer(time_t startTime);

  virtual void timePassed(uint ms);
  time_t getDBTime() const;

private:
  time_t time_;
  uint currentMs_;
};

typedef std::shared_ptr<Timer> TimerPtr;

}//namespace SimCity
}//namespace Model


#endif // TIMER_H
