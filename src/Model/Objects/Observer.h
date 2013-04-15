#ifndef OBSERVER_H
#define OBSERVER_H
#include <Model/Objects/ObjectSnapshot.h>
#include <Model/SimulationPart.h>

namespace SimCity
{
namespace Model
{

class Map;
class World;

namespace Objects
{

class Observer : public SnapshotVisitor,
                 public SimulationPart
{
public:
  Observer(const Map& map);
  virtual ~Observer();

  virtual void accept(World& w) = 0;
  virtual void provideObjects(const Objects::Snapshots& obj);

  /**`
   * @brief timePassed - derived from SimulationPart
   * @see SimulationPart::timePassed
   */
  virtual void timePassed(int ms) = 0;

protected:
  const Map& map_;
  Objects::Snapshots objects_;
};

}//namesapce Objects
}//namespace SimCity
}//namespace Model
#endif // OBSERVER_H
