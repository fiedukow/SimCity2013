#ifndef OBJECTS_H
#define OBJECTS_H
#include <Model/Objects/LiveObject.h>
#include <Model/Objects/ObjectSnapshot.h>

namespace SimCity
{
namespace Model
{
namespace Objects
{

class Car : public LiveObject
{
public:
  Car(const MapPtr map,
      const Physics::Position& pos,
      const Physics::Velocity& v);
  virtual ~Car();

  virtual SnapshotPtr getSnapshot() const;
  virtual Physics::Mass getCurrentMass() const;
  virtual Physics::Force getCurrentForce() const;
};

}//namesapce Objects
}//namespace SimCity
}//namespace Model


#endif // OBJECTS_H
