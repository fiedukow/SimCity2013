#ifndef OBSERVERS_H
#define OBSERVERS_H
#include <Model/Objects/Observer.h>

namespace SimCity
{
namespace Model
{
namespace Objects
{

class RoadUserObserver : virtual public Observer
{
public:
  RoadUserObserver(const MapPtr& map);
  virtual ~RoadUserObserver();

  void visit(CarSnapshot& car);
  void visit(PedestrianSnapshot& pedestrian);
  void visit(SensorSnapshot& snapshot);

  void accept(World &w);
};

class SensorObserver : virtual public Observer
{
public:
  SensorObserver(const MapPtr& map);
  virtual ~SensorObserver();

  void visit(CarSnapshot& car) = 0;
  void visit(SensorSnapshot& snapshot) = 0;

  void accept(World &w);
};

}//namespace Objects
}//namespace Model
}//namespace SimCity

#endif // OBSERVERS_H
