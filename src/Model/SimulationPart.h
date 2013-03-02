#ifndef SIMULATIONPART_H
#define SIMULATIONPART_H

#include <Common/GeneralTypes.h>

namespace SimCity
{
namespace Model
{

/**
 * @brief SimulationPart - element that should be informed about passing time
 *
 * This is interface for elements that can react for time passage.
 * Classes like world and object will derive from this and Model will call
 * timePassed method on them.
 */
class SimulationPart
{
public:
  virtual ~SimulationPart();
  /**
   * @brief timePassed virtual method which call causes to do action connected
   * with passed time period
   * @param ms - time in miliseconds that passed (simulation time).
   */
  virtual void timePassed(uint ms) = 0;
};

}//namespace SimCity
}//namespace Model

#endif // SIMULATIONPART_H
