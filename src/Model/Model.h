#ifndef MODEL_H
#define MODEL_H
#include <Common/GeneralTypes.h>
#include <Common/NewStateObserver.h>
#include <Model/SimulationPart.h>
#include <list>
#include <memory>

#include <boost/thread/shared_mutex.hpp>

namespace boost
{
class thread;
}

namespace SimCity
{
namespace Model
{

typedef std::list<SimulationPartPtr> SimParts;
typedef std::list<Common::NewStateObserver*> ObserversList;

class Model
{
public:
  Model();

  /**
   * @brief registerNewStateObserver - allows to add new observer of model state
   * @param obs - pointer to the observer you want to inform about changes
   * @warning If object under pointer will be deleted you must call
   *          unregisterNewStateObserver to avoid calling methods on dead object
   * @see unregisterNewStateObserver()
   */
  void registerNewStateObserver(Common::NewStateObserver* obs);

  /**
   * @brief unregisterNewStateObserver - allows to remove state observer
   * @param obs - pointer to observer you want to remove from observers
   * @see registerNewStateObserver()
   */
  void unregisterNewStateObserver(Common::NewStateObserver* obs);

  /**
   * @brief start - starts simulation from scrach or continue if it was paused
   */
  void start();

  /**
   * @brief stop - stops simulation removing current state
   * @note it's impossible to continue this simulation after calling stop()
   */
  void stop();

  /**
   * @brief pause - pauses model run but renumbers current state of simulation
   * @note this will only stops processing until start() will be called
   * @see start()
   */
  void pause();

  /**
   * @brief Model::addSimulationPart - adds new element to simulations
   * @param newSimPart - part of simulation to add to the simulation
   * @warning Dont try to call this method if simulation thread is already
   *          running
   */
  void addSimulationPart(SimulationPartPtr newSimPart);

  /**
   * @brief operator() starts simulation thread
   * @see start()
   * @see stop()
   * @see pause()
   */
  void operator()();

protected:
  /**
   * @brief notifyNewStateObservers - calls notify on all registred observers
   */
  void notifyNewStateObservers();

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

  bool paused_;

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

  /**
   * @brief newStateObservers_ - list of new state observers to be informed
   *        about changes
   */
  ObserversList newStateObservers_;

  /**
   * @brief thread_ - pointer to current thread of model if it exists or NULL
   */
  boost::thread* thread_;

  /**
   * @brief pauseMutex_ - mutex checked on every loop cycle in model thread
   * Locking this mutex causes thread to pause on next loop cycle.
   * @see pause()
   */
  boost::shared_mutex pauseMutex_;
};

}//namespace SimCity
}//namespace Model


#endif // MODEL_H
