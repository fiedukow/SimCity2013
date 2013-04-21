#ifndef OBJECTS_H
#define OBJECTS_H
#include <Model/Objects/LiveObject.h>
#include <Model/Objects/ObjectSnapshot.h>
#include <Model/Objects/Observers.h>

namespace SimCity
{
namespace Model
{
namespace Objects
{

class Car : public LiveObject,
            public CarObserver
{
public:
  enum Direction { FS = 0, /*from first node to second node*/
                   SF = 1  /*from second node to first node*/};

public:
  Car(const MapPtr map,
      const Physics::Position& pos,
      const StreetPtr street,
      const Direction direction,
      const bool isQuick);
  virtual ~Car();

  void timePassed(uint ms);

  virtual SnapshotPtr getSnapshot() const;
  virtual Physics::Mass getCurrentMass() const;
  virtual Physics::Force getCurrentForce() const;

  bool isMad() const;

private:
  void newStreet();
  void newStreet(StreetNodePtr streetNode);
  void newVelocity(double min = 5.0, double max = 35.0);

  StreetNodePtr getStartNode() const;
  StreetNodePtr getDesitinationNode() const;
  Physics::Position getStartPosition() const;
  Physics::Position getDestinationPosition() const;
  bool isRoadFinishedThisStep(uint ms);

private:
  StreetPtr street_;
  Direction direction_;
  double lastDistance_;
  bool isQuick_;
};

class RadiusSensor : public LiveObject,
                     public SensorObserver
{
public:
  RadiusSensor(uint id,
               const MapPtr& map,
               const Physics::Position& pos,
               const Physics::Angle& fov,
               const double range);
  virtual ~RadiusSensor();

  void timePassed(uint ms);

  virtual SnapshotPtr getSnapshot() const;
  virtual Physics::Mass getCurrentMass() const;
  virtual Physics::Force getCurrentForce() const;

  bool isInRange(Snapshot& object);

  void visit(CarSnapshot& car);
  void visit(SensorSnapshot& snapshot);

  double getRange() const;

private:
  uint id_;
  Physics::Angle fov_;
  double range_;
  uint timeCounter_;
};

}//namesapce Objects
}//namespace SimCity
}//namespace Model


#endif // OBJECTS_H
