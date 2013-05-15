#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H
#include <Model/SimulationPart.h>
#include <Model/Model.h>
#include <list>
#include <Model/Objects/LiveObject.h>

namespace SimCity
{
namespace Model
{
using Objects::LiveObjectPtr;
typedef std::list<LiveObjectPtr> LiveObjects;

class ObjectManager : public SimulationPart
{
public:
  ObjectManager(WorldPtr world,
                const std::string& dbName,
                const std::string& dbUser,
                const std::string& dbPassword,
                uint limit = 10,
                uint pedestrianLimit = 1);
  virtual ~ObjectManager();

  virtual void timePassed(uint ms);
  void setCarLimit(uint limit);
  void setPedestrianLimit(uint limit);

private:
  WorldPtr world_;
  uint limit_;
  uint pedestrianLimit_;
  LiveObjects objects_;
  LiveObjects pedestrians_;
};

typedef std::shared_ptr<ObjectManager> ObjectManagerPtr;

}//namespace SimCity
}//namespace Model

#endif // OBJECTMANAGER_H
