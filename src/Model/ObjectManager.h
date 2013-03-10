#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H
#include <Model/SimulationPart.h>

namespace SimCity
{
namespace Model
{

class ObjectManager : public SimulationPart
{
public:
  ObjectManager();
  virtual ~ObjectManager();
  virtual void timePassed(uint ms);
};

}//namespace SimCity
}//namespace Model

#endif // OBJECTMANAGER_H
