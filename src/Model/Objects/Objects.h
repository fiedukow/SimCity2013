#ifndef OBJECTS_H
#define OBJECTS_H
#include <Model/Objects/LiveObject.h>
#include <Model/Objects/ObjectSnapshot.h>
#include <Model/Objects/Observers.h>

namespace SimCity
{
namespace Model
{
namespace Objects
{

class Car : public LiveObject,
            virtual public CarObserver
{
public:
  enum Direction { FS = 0, /*from first node to second node*/
                   SF = 1  /*from second node to first node*/};

public:
  Car(const MapPtr map,
      const Physics::Position& pos,
      const Physics::Velocity& v,
      const StreetPtr street,
      const Direction direction);
  virtual ~Car();

  void timePassed(uint ms);

  virtual SnapshotPtr getSnapshot() const;
  virtual Physics::Mass getCurrentMass() const;
  virtual Physics::Force getCurrentForce() const;

private:
  StreetPtr street_;
  Direction direction_;
};

}//namesapce Objects
}//namespace SimCity
}//namespace Model


#endif // OBJECTS_H
