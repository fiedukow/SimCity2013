#ifndef WORLD_H
#define WORLD_H

#include <Model/SimulationPart.h>
#include <Model/DBDataStructures.h>
#include <Model/Objects/Object.h>
#include <Model/Objects/ObjectSnapshot.h>

#include <list>
#include <memory>

namespace SimCity
{
namespace Model
{

using namespace Objects;
typedef std::list<PlacedObject> PlacedObjects;

class World : public SimulationPart
{
public:
  World(const std::string& dbName,
        const std::string& dbUser,
        const std::string& dbPassword);
  virtual ~World();
  virtual void timePassed(uint ms);

  MapPtr getMapSnapshot();
  Snapshots getObjectSnapshots();

  static MapPtr readMapFromDB(const std::string& dbName,
                              const std::string& dbUser,
                              const std::string& dbPassword);

private:
  MapPtr map_;
  PlacedObjects objects_;
};

}//namespace Model
}//namespace SimCity

#endif // WORLD_H
