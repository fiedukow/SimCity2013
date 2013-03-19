#ifndef OBJECTS_H
#define OBJECTS_H
#include <Model/Objects/Object.h>
#include <Model/Objects/ObjectSnapshot.h>

namespace SimCity
{
namespace Model
{
namespace Objects
{

class PowerBall : public Object
{
public:
  virtual SnapshotPtr getSnapshot(const PlacedObject&) const;
  virtual Physics::Mass getCurrentMass() const;
  virtual Physics::Force getCurrentForce() const;
};

}//namesapce Objects
}//namespace SimCity
}//namespace Model


#endif // OBJECTS_H
