#ifndef OBSERVERS_H
#define OBSERVERS_H
#include <Model/Objects/Observer.h>

namespace SimCity
{
namespace Model
{
namespace Objects
{

class CarObserver : virtual public Observer
{
public:
  CarObserver(const MapPtr& map);
  virtual ~CarObserver();

  void visit(CarSnapshot& car);

  void accept(World &w);
};

}//namespace Objects
}//namespace Model
}//namespace SimCity

#endif // OBSERVERS_H
