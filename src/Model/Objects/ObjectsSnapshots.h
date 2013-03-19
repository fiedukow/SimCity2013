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

class PowerBallSnapshot : public Snapshot
{
public:
  PowerBallSnapshot(const PlacedObject &object);
  virtual ~PowerBallSnapshot();

  virtual void accept(SnapshotVisitor& visitor);
};

}//namesapce Objects
}//namespace SimCity
}//namespace Model


#endif // OBJECTSSNAPSHOTS_H
