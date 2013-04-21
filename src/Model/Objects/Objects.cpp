#include "Objects.h"
#include <Common/GlobalLogger.h>
#include <Model/Objects/ObjectsSnapshots.h>
#include <limits>
#include <iostream>

#define SNAPSHOT_PERIOD 3000
//TODO ^^ avoid define please.

namespace SimCity
{
namespace Model
{
namespace Objects
{

Car::Car(const MapPtr map,
         const Physics::Position& pos,
         const StreetPtr street,
         const Direction direction,
         const bool isQuick)
  : Observer(map),
    LiveObject(map, pos, Physics::Velocity(Physics::Vector3(0, 0, 0))),
    CarObserver(map),
    street_(street),
    direction_(direction),
    lastDistance_(std::numeric_limits<double>::infinity()),
    isQuick_(isQuick)
{
  newVelocity();
}

Car::~Car()
{}

void Car::timePassed(uint ms)
{
  if(!isRoadFinishedThisStep(ms))
    return;

  newStreet();
  newVelocity();
}

void Car::newStreet()
{
  newStreet(getDesitinationNode());
}

void Car::newStreet(StreetNodePtr startNode)
{
  Streets toChoose = map_->streetsInVertex(startNode);
  StreetPtr tmpStreet = toChoose[rand()%toChoose.size()];
  while(tmpStreet == street_ && toChoose.size() > 1)
    tmpStreet = toChoose[rand()%toChoose.size()];

  street_ = tmpStreet;
  direction_ = street_->first == startNode ? FS : SF;
  pos = getStartPosition();
}

void Car::newVelocity(double min, double max)
{
  double speed = ((double)rand()/(double)RAND_MAX)*(max-min)+min;
  if(isQuick_)
    speed *= 5.0;
  std::cout << "Velocity: " << speed << std::endl;
  double dx = (getStartPosition().x - getDestinationPosition().x);
  double dy = (getStartPosition().y - getDestinationPosition().y);
  double d  = sqrt(pow(dx, 2) + pow(dy, 2));
  double timeInSeconds = d/speed;
  Physics::TimeDuration t(timeInSeconds);
  v = Physics::Velocity((getDestinationPosition()-getStartPosition())/t);
}

Physics::Position Car::getStartPosition() const
{
  return Physics::Position(Physics::GeoCoords(getStartNode()->lon.get(),
                                              getStartNode()->lat.get()));
}

Physics::Position Car::getDestinationPosition() const
{
  return Physics::Position(Physics::GeoCoords(getDesitinationNode()->lon.get(),
                                              getDesitinationNode()->lat.get()));
}

SnapshotPtr Car::getSnapshot() const
{
  return SnapshotPtr(new CarSnapshot(*this));
}

Physics::Mass Car::getCurrentMass() const
{
  return Physics::Mass(1000.0);
}

Physics::Force Car::getCurrentForce() const
{
  return Physics::Force(Physics::Vector3(0.0, 0.0, 0.0));
}

StreetNodePtr Car::getStartNode() const
{
  return direction_ == FS ? street_->first : street_->second;
}

StreetNodePtr Car::getDesitinationNode() const
{
  return direction_ == FS ? street_->second : street_->first;
}

bool Car::isRoadFinishedThisStep(uint ms)
{
  Physics::TimeDuration t(ms/1000.0);
  Physics::Shift mv = v * t;
  Physics::Position newPos = pos + mv;
  double currDist = pos.distance(getDestinationPosition());
  double nextDist = newPos.distance(getDestinationPosition());

  if(nextDist < currDist)
    return false;

  return true;
}

Sensor::Sensor(const MapPtr& map,
               const Physics::Position& pos,
               const Physics::Angle& fov,
               const double range)
  : Observer(map),
    LiveObject(map, pos, Physics::Velocity(Physics::Vector3(0, 0, 0))),
    SensorObserver(map),
    fov_(fov),
    range_(range),
    timeCounter_(rand()%SNAPSHOT_PERIOD)
{
}

Sensor::~Sensor()
{}

void Sensor::timePassed(uint ms)
{
  timeCounter_ += ms;
  if(timeCounter_ < SNAPSHOT_PERIOD)
    return;

  timeCounter_ -= SNAPSHOT_PERIOD;
  for(SnapshotPtr snapshot : objects_)
    snapshot->accept(*this);
}

SnapshotPtr Sensor::getSnapshot() const
{
  return SnapshotPtr(new SensorSnapshot(*this));
}

Physics::Mass Sensor::getCurrentMass() const
{
  return Physics::Mass(1.0);
}

Physics::Force Sensor::getCurrentForce() const
{
  return Physics::Force(Physics::Vector3(0, 0, 0));
}

bool Sensor::isInRange(Snapshot& object)
{
  double dist = object.getPosition().distance(pos);
  return (dist <= range_ && dist >= 0.01); //TODO avoid magic const
}

void Sensor::visit(CarSnapshot& car)
{
  if(!isInRange(car))
    return;

  Physics::GeoCoords geo(car.getPosition());

  std::cout << "I see car in: "
            << geo.lon << ", "
            << geo.lat << ", "
            << geo.mos << "."
            << std::endl;
}

void Sensor::visit(SensorSnapshot& snapshot)
{
  if(!isInRange(snapshot))
    return;

  Physics::GeoCoords geo(snapshot.getPosition());

  std::cout << "I see camera in: "
            << geo.lon << ", "
            << geo.lat << ", "
            << geo.mos << "."
            << std::endl;
}

double Sensor::getRange() const
{
  return range_;
}

}//namesapce Objects
}//namespace SimCity
}//namespace Model

