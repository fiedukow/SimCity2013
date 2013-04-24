#ifndef OBJECTSSNAPSHOTS_H
#define OBJECTSSNAPSHOTS_H
#include <Model/Objects/ObjectSnapshot.h>
#include <Model/Objects/Objects.h>

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
  CarSnapshot(const Car &object);
  virtual ~CarSnapshot();

  virtual void accept(SnapshotVisitor& visitor);
  bool isMad() const;

private:
  bool isMad_;
};

class PedestrianSnapshot : public Snapshot
{
public:
  PedestrianSnapshot(const Pedestrian &object);
  virtual ~PedestrianSnapshot();

  virtual void accept(SnapshotVisitor& visitor);
  bool isMad() const;

private:
  bool isMad_;
};

class SensorSnapshot : public Snapshot
{
public:
  SensorSnapshot(const RadiusSensor& object);
  virtual ~SensorSnapshot();

  double getRange() const;

  virtual void accept(SnapshotVisitor& visitor);

private:
  double range_;
};

}//namesapce Objects
}//namespace SimCity
}//namespace Model


#endif // OBJECTSSNAPSHOTS_H
