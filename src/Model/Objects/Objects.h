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

class RoadUser : public LiveObject,
                 public RoadUserObserver
{
public:
  enum Direction { FS = 0, /*from first node to second node*/
                   SF = 1  /*from second node to first node*/};

public:
  RoadUser(const MapPtr map);
  RoadUser(const MapPtr map,
           const Physics::Position& pos,
           const StreetPtr street,
           const Direction direction);
  virtual ~RoadUser();

  void timePassed(uint ms);

  virtual SnapshotPtr getSnapshot() const = 0;
  virtual Physics::Mass getCurrentMass() const = 0;
  virtual Physics::Force getCurrentForce() const = 0;

  virtual double getNextSpeed() const = 0;

protected:
  void initialize();

private:
  void newStreet();
  void newStreet(StreetNodePtr streetNode);
  void newVelocity();
  void newVelocity(double speed);

  StreetNodePtr getStartNode() const;
  StreetNodePtr getDesitinationNode() const;
  Physics::Position getStartPosition() const;
  Physics::Position getDestinationPosition() const;
  bool isRoadFinishedThisStep(uint ms);

private:
  StreetPtr street_;
  Direction direction_;
  double lastDistance_;
};

class Car : public RoadUser
{
public:
  Car(const MapPtr map,
      const bool isQuick);
  Car(const MapPtr map,
      const Physics::Position& pos,
      const StreetPtr street,
      const Direction direction,
      const bool isQuick);
  ~Car();

  virtual SnapshotPtr getSnapshot() const;
  virtual Physics::Mass getCurrentMass() const;
  virtual Physics::Force getCurrentForce() const;

  bool isMad() const;

protected:
  virtual double getNextSpeed() const;

private:
  bool isQuick_;

private:
  static double minSpeed_;
  static double maxSpeed_;
};

class Pedestrian : public RoadUser
{
public:
  Pedestrian(const MapPtr map,
             const bool isQuick);
  Pedestrian(const MapPtr map,
             const Physics::Position& pos,
             const StreetPtr street,
             const Direction direction,
             const bool isQuick);
  ~Pedestrian();

  virtual SnapshotPtr getSnapshot() const;
  virtual Physics::Mass getCurrentMass() const;
  virtual Physics::Force getCurrentForce() const;

  bool isMad() const;

protected:
  virtual double getNextSpeed() const;

private:
  bool isQuick_;

private:
  static double minSpeed_;
  static double maxSpeed_;
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
  void visit(PedestrianSnapshot& pedestrian);
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
