#include "Objects.h"
#include <Common/GlobalLogger.h>
#include <Model/Objects/ObjectsSnapshots.h>
#include <limits>
#include <iostream>

namespace SimCity
{
namespace Model
{
namespace Objects
{

Car::Car(const MapPtr map,
         const Physics::Position& pos,
         const Physics::Velocity& v,
         const StreetPtr street,
         const Direction direction,
         const bool isQuick)
  : Observer(map),
    LiveObject(map, pos, v),
    CarObserver(map),
    street_(street),
    direction_(direction),
    lastDistance_(std::numeric_limits<double>::infinity()),
    isQuick_(isQuick)
{}

Car::~Car()
{}

void Car::timePassed(uint)
{
  if(!isRoadFinished())
    return;

  StreetNodePtr destNode = getDesitinationNode();
  Streets toChoose = map_->streetsInVertex(destNode);
  StreetPtr tmpStreet = toChoose[rand()%toChoose.size()];
  while(tmpStreet == street_ && toChoose.size() > 1)
    tmpStreet = toChoose[rand()%toChoose.size()];

  street_ = tmpStreet;
  direction_ = street_->first == destNode ? FS : SF;

  StreetNodePtr startNode = getStartNode();
  StreetNodePtr endNode = getDesitinationNode();

  Physics::Position startPos(Physics::GeoCoords(startNode->lon.get(),
                                                startNode->lat.get()));
  Physics::Position endPos(Physics::GeoCoords(endNode->lon.get(),
                                              endNode->lat.get()));
  double randTime = 5.0 + (rand()%100)/10.0;
  if(isQuick_)
    randTime /= 3.0;
  Physics::Velocity startV((endPos-startPos)/Physics::TimeDuration(randTime));

  v = startV;
  pos = startPos;
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

bool Car::isRoadFinished()
{
  Physics::Position endPos(Physics::GeoCoords(getDesitinationNode()->lon.get(),
                                              getDesitinationNode()->lat.get()));
  double currDist = pos.distance(endPos);
  if(lastDistance_ > currDist)
  {
    lastDistance_ = currDist;
    return false;
  }

  lastDistance_ = std::numeric_limits<double>::infinity();
  return true;
}



Sensor::Sensor(const MapPtr& map,
               const Physics::Position& pos,
               const Physics::Angle& fov,
               const double range)
  : Observer(map),
    LiveObject(map, pos, Physics::Velocity(Physics::Vector3(0,0,0))),
    SensorObserver(map),
    fov_(fov),
    range_(range),
    timeCounter_(0)
{
}

Sensor::~Sensor()
{}

void Sensor::timePassed(uint ms)
{
  timeCounter_ += ms;
  if(timeCounter_ < 1000) //TODO parameterizable
    return;

  timeCounter_ = 0;
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


void Sensor::visit(CarSnapshot& car)
{
  double dist = car.getPosition().distance(pos);
  if(dist > range_
     || dist < 0.01) //TODO remove this magic const
    return;

  Physics::GeoCoords geo(car.getPosition());
  Physics::GeoCoords myGeo(pos);

  std::cout << "My position is: "
            << myGeo.lon << ", "
            << myGeo.lat << ", "
            << myGeo.mos << "."
            << std::endl;

  std::cout << "I see car in: "
            << geo.lon << ", "
            << geo.lat << ", "
            << geo.mos << "."
            << std::endl;
}

void Sensor::visit(SensorSnapshot& snapshot)
{
  double dist = snapshot.getPosition().distance(pos);
  if(snapshot.getPosition().distance(pos) > range_
     || dist < 0.01) //TODO remove this magic const
    return;

  Physics::GeoCoords geo(snapshot.getPosition());
  Physics::GeoCoords myGeo(pos);

  std::cout << "My position is: "
            << myGeo.lon << ", "
            << myGeo.lat << ", "
            << myGeo.mos << "."
            << std::endl;

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

