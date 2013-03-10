#ifndef OBJECT_H
#define OBJECT_H
#include <Model/Physics/NewtonsDynamics.h>

namespace SimCity
{
namespace Model
{

class Object
{
public:
  Object();

  virtual void getSnapshot() const = 0; //TODO it is no void returning
  virtual Physics::Mass getCurrentMass() const = 0;   //Argh...
                                                      //Heisenberg would kill me
                                                      // for this const here...
  virtual Physics::Force getCurrentForce() const = 0;
};

}//namespace SimCity
}//namespace Model

#endif // OBJECT_H
