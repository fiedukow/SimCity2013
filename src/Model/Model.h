#ifndef MODEL_H
#define MODEL_H
#include <Common/GeneralTypes.h>
#include <Model/SimulationPart.h>
#include <list>
#include <memory>

namespace SimCity
{
namespace Model
{

typedef std::list<SimulationPartPtr> SimParts;

class Model
{
public:
  Model();

  /**
   * @brief operator() starts simulation thread
   */
  void operator()();

  /**
   * @brief Model::addSimulationPart - adds new element to simulations
   * @param newSimPart - part of simulation to add to the simulation
   * @warning Dont try to call this method if simulation thread is already
   *          running
   */
  void addSimulationPart(SimulationPartPtr newSimPart);

  /**
   * @brief stopAllThreads - stops simulation thread(s)
   */
  void stopAllThreads();

private:
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

  /**
   * @brief threadRunning_ - will be set when thread is running
   * @note use this to determine if some methods can be invoked in given context
   */
  bool threadRunning_;

  /**
   * @brief simParts_ parts of simulation collection
   * In this collection there are all elements that are part of simulation
   * like world, object manager etc.
   * Every element of this collection will be informed about time passing
   * in simulation but none of those will now nothing about real time flow.
   */
  SimParts simParts_;
};

}//namespace SimCity
}//namespace Model


#endif // MODEL_H
