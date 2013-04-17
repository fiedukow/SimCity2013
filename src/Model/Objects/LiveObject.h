#ifndef LIVEOBJECT_H
#define LIVEOBJECT_H
#include <Model/Objects/Object.h>
#include <Model/Objects/Observer.h>
#include <memory>

namespace SimCity
{
namespace Model
{
namespace Objects
{

class LiveObject : public PlacedObject,
                   virtual public Observer
{
public:
  LiveObject(const MapPtr map,
             const Physics::Position& pos,
             const Physics::Velocity& v);
  virtual ~LiveObject();
};

typedef std::shared_ptr<LiveObject> LiveObjectPtr;

}//namespace Objects
}//namespace Model
}//namespace SimCity

#endif // LIVEOBJECT_H
