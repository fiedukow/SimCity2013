#ifndef OBJECTSSNAPSHOTS_H
#define OBJECTSSNAPSHOTS_H
#include <Model/Objects/ObjectSnapshot.h>

namespace SimCity
{
namespace Model
{
namespace Objects
{

class SnapshotVisitor;

class CarSnapshot : public Snapshot
{
public:
  CarSnapshot(const PlacedObject &object);
  virtual ~CarSnapshot();

  virtual void accept(SnapshotVisitor& visitor);
};

}//namesapce Objects
}//namespace SimCity
}//namespace Model


#endif // OBJECTSSNAPSHOTS_H
