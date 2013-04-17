#ifndef WORLD_H
#define WORLD_H

#include <Model/SimulationPart.h>
#include <Model/DBDataStructures.h>
#include <Model/Objects/Object.h>
#include <Model/Objects/Observer.h>
#include <Model/Objects/ObjectSnapshot.h>
#include <Model/Objects/Observers.h>

#include <list>
#include <memory>

namespace SimCity
{
namespace Model
{

using namespace Objects;
typedef std::list<PlacedObjectPtr> PlacedObjects;
typedef std::list<ObserverPtr> Observers;

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

  void updateObjectSnapshots();

  void visit(CarObserver& car);

  void addPlacedObject(PlacedObjectPtr obj);
  void removePlacedObject(PlacedObjectPtr obj);

  void addObserver(ObserverPtr obs);
  void removeObserver(ObserverPtr obs);

  static MapPtr readMapFromDB(const std::string& dbName,
                              const std::string& dbUser,
                              const std::string& dbPassword);

private:
  MapPtr map_;
  PlacedObjects objects_;
  Observers observers_;
  Snapshots snapshot_;
};

}//namespace Model
}//namespace SimCity

#endif // WORLD_H
