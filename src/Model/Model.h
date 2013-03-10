#ifndef MODEL_H
#define MODEL_H
#include <Common/GeneralTypes.h>
#include <Model/SimulationPart.h>
#include <vector>

namespace SimCity
{
namespace Model
{

class Model
{
public:
  Model();
  void operator()();
  void stopAllThreads();

private:

  ptime lastTickTime;

  /**
   * @brief minTimerDelay - minimal time between ticks
   * This is minimal time between two ticks controlled by timer.
   * The real time of tick is measured by deltas between two ticks triggers.
   */
  uint minTimerDelay;

  /**
   * @brief simulationSpeed - speed of simulation
   * This is factor between real time and time of simulation
   * eg. 1.0 means 1s in real time is 1s in simulation
   *     2.0 means 1s in real time is 2s in simulation
   */
  double simulationSpeed;

  /**
   * @brief pollingPeriod - sleep in ms between checking if minTimerDelay is up
   */
  const double pollingPeriod;

  /**
   * @brief stopThreads_
   * If it is set every thread in model should be stopped as soon as possible.
   */
  bool stopThreads_;
};

}//namespace SimCity
}//namespace Model


#endif // MODEL_H
