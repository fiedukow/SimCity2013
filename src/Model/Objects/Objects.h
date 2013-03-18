#ifndef OBJECTS_H
#define OBJECTS_H
#include <Model/Objects/Object.h>

namespace SimCity
{
namespace Model
{
namespace Objects
{

class PowerBall : public Object
{
  virtual void getSnapshot() const;
  virtual Physics::Mass getCurrentMass() const;
  virtual Physics::Force getCurrentForce() const;
};

}//namesapce Objects
}//namespace SimCity
}//namespace Model


#endif // OBJECTS_H
