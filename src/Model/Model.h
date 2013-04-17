#ifndef MODEL_H
#define MODEL_H
#include <Common/GeneralTypes.h>
#include <Common/NewStateObserver.h>
#include <Model/SimulationPart.h>
#include <Model/DBDataStructures.h>
#include <Model/Objects/ObjectSnapshot.h>
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

class World;
typedef std::list<SimulationPartPtr> SimParts;
typedef std::list<Common::NewStateObserver*> ObserversList;
typedef std::shared_ptr<World> WorldPtr;

class Model
{
public:
  Model(const WorldPtr world);

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
   * @brief setSimulationSpeed - allows to change speed of simulation even
   *                             in progress
   * @param speed - speed relative to real (eg. 1.0 is natural speed, 0.5 is
   *                two times slower).
   */
  void setSimulationSpeed(double speed);

  /**
   * @brief getMapSnapshot - gets current map snapshot as shared pointer
   * @returns MapPtr -shared pointer to current map state.
   */
  MapPtr getMapSnapshot();

  /**
   * @brief getObjectSnapshots
   * @return - container with snapshots of all objects in world
   */
  Objects::Snapshots getObjectSnapshots();

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
  uint minTimerDelay_;

  /**
   * @brief simulationSpeed - speed of simulation
   * This is factor between real time and time of simulation
   * eg. 1.0 means 1s in real time is 1s in simulation
   *     2.0 means 1s in real time is 2s in simulation
   */
  double simulationSpeed_;

  /**
   * @brief pollingPeriod - sleep in ms between checking if minTimerDelay is up
   */
  const double pollingPeriod_;

  /**
   * @brief stopThreads_
   * If it is set every thread in model should be stopped as soon as possible.
   */
  bool stopThreads_;

  /**
   * @brief paused_ - is set to true when the thread is in pause state
   */
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
   * @brief world_ - this is special simulation part having access to state
   *                 that will be presented to user.
   * @note It is keept in simParts_ collection too
   * @see Model::simParts_
   */
  WorldPtr world_;

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
  boost::mutex pauseMutex_;
};

}//namespace SimCity
}//namespace Model


#endif // MODEL_H
