#include "Objects.h"
#include <Common/GlobalLogger.h>
#include <Model/Objects/ObjectsSnapshots.h>
#include <limits>
#include <iostream>
#include <ctime>

#include <3rd/DynDbDriver/dyndbdriver.h>

#define SNAPSHOT_PERIOD 3000
//TODO ^^ avoid define please.

namespace SimCity
{
namespace Model
{
namespace Objects
{

RoadUser::RoadUser(const MapPtr map)
  :Observer(map),
   LiveObject(map,
              Physics::Position(0, 0, 0),
              Physics::Velocity(Physics::Vector3(0, 0, 0))),
   RoadUserObserver(map),
   lastDistance_(std::numeric_limits<double>::infinity())
{
  street_ = map->edges[rand()%map->edges.size()];
  direction_ = rand()%2 ? Car::FS : Car::SF;
  pos = getStartPosition();
}

RoadUser::RoadUser(const MapPtr map,
                   const Physics::Position& pos,
                   const StreetPtr street,
                   const Direction direction)
  : Observer(map),
    LiveObject(map, pos, Physics::Velocity(Physics::Vector3(0, 0, 0))),
    RoadUserObserver(map),
    street_(street),
    direction_(direction),
    lastDistance_(std::numeric_limits<double>::infinity())
{}

RoadUser::~RoadUser()
{}

void RoadUser::initialize()
{
  newVelocity();
}

void RoadUser::timePassed(uint ms)
{
  if(!isRoadFinishedThisStep(ms))
    return;

  newStreet();
  newVelocity();
}

void RoadUser::newStreet()
{
  newStreet(getDesitinationNode());
}

void RoadUser::newStreet(StreetNodePtr startNode)
{
  Streets toChoose = map_->streetsInVertex(startNode);
  StreetPtr tmpStreet = toChoose[rand()%toChoose.size()];
  while(tmpStreet == street_ && toChoose.size() > 1)
    tmpStreet = toChoose[rand()%toChoose.size()];

  street_ = tmpStreet;
  direction_ = street_->first == startNode ? FS : SF;
  pos = getStartPosition();
}

void RoadUser::newVelocity()
{
  newVelocity(getNextSpeed());
}

void RoadUser::newVelocity(double speed)
{
  std::cout << "Velocity: " << speed << std::endl;
  double dx = (getStartPosition().x - getDestinationPosition().x);
  double dy = (getStartPosition().y - getDestinationPosition().y);
  double d  = sqrt(pow(dx, 2) + pow(dy, 2));
  double timeInSeconds = d/speed;
  Physics::TimeDuration t(timeInSeconds);
  v = Physics::Velocity((getDestinationPosition()-getStartPosition())/t);
}

Physics::Position RoadUser::getStartPosition() const
{
  return Physics::Position(Physics::GeoCoords(getStartNode()->lon.get(),
                                              getStartNode()->lat.get()));
}

Physics::Position RoadUser::getDestinationPosition() const
{
  return Physics::Position(Physics::GeoCoords(getDesitinationNode()->lon.get(),
                                              getDesitinationNode()->lat.get()));
}

StreetNodePtr RoadUser::getStartNode() const
{
  return direction_ == FS ? street_->first : street_->second;
}

StreetNodePtr RoadUser::getDesitinationNode() const
{
  return direction_ == FS ? street_->second : street_->first;
}

bool RoadUser::isRoadFinishedThisStep(uint ms)
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

/******************************************************************************/
/******************************************************************************/

double Car::minSpeed_ = 5.0;
double Car::maxSpeed_ = 35.0;

Car::Car(const MapPtr map,
         const bool isQuick)
  : Observer(map),
    RoadUser(map),
    isQuick_(isQuick)
{
  initialize();
}

Car::Car(const MapPtr map,
         const Physics::Position& pos,
         const StreetPtr street,
         const Direction direction,
         const bool isQuick)
  : Observer(map),
    RoadUser(map, pos, street, direction),
    isQuick_(isQuick)
{
  initialize();
}

Car::~Car()
{}

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

bool Car::isMad() const
{
  return isQuick_;
}

double Car::getNextSpeed() const
{
  double speed = ((double)rand()/(double)RAND_MAX); //random between 0.0 and 1.0
  speed *= (maxSpeed_ - minSpeed_);
  speed += minSpeed_;
  if(isQuick_)
    speed *= 5.0;
  return speed;
}

/******************************************************************************/
/******************************************************************************/

double Pedestrian::minSpeed_ = 1.0;
double Pedestrian::maxSpeed_ = 2.0;

Pedestrian::Pedestrian(const MapPtr map,
                       const bool isQuick)
  : Observer(map),
    RoadUser(map),
    isQuick_(isQuick)
{
  initialize();
}

Pedestrian::Pedestrian(const MapPtr map,
                       const Physics::Position& pos,
                       const StreetPtr street,
                       const Direction direction,
                       const bool isQuick)
  : Observer(map),
    RoadUser(map, pos, street, direction),
    isQuick_(isQuick)
{
  initialize();
}

Pedestrian::~Pedestrian()
{}

SnapshotPtr Pedestrian::getSnapshot() const
{
  return SnapshotPtr(new PedestrianSnapshot(*this));
}

Physics::Mass Pedestrian::getCurrentMass() const
{
  return Physics::Mass(60.0);
}

Physics::Force Pedestrian::getCurrentForce() const
{
  return Physics::Force(Physics::Vector3(0.0, 0.0, 0.0));
}

bool Pedestrian::isMad() const
{
  return isQuick_;
}

double Pedestrian::getNextSpeed() const
{
  double speed = ((double)rand()/(double)RAND_MAX); //random between 0.0 and 1.0
  speed *= (maxSpeed_ - minSpeed_);
  speed += minSpeed_;
  if(isQuick_)
    speed *= 10.0;
  return speed;
}

/******************************************************************************/
/******************************************************************************/

RadiusSensor::RadiusSensor(uint id,
                           const MapPtr map,
                           const TimerPtr timer,
                           const Physics::Position& pos,
                           const Physics::Angle& fov,
                           const double range)
  : Observer(map),
    LiveObject(map, pos, Physics::Velocity(Physics::Vector3(0, 0, 0))),
    SensorObserver(map),
    id_(id),
    timer_(timer),
    fov_(fov),
    range_(range),
    timeCounter_(rand()%SNAPSHOT_PERIOD)
{
}

RadiusSensor::~RadiusSensor()
{}

void RadiusSensor::timePassed(uint ms)
{
  timeCounter_ += ms;
  if(timeCounter_ < SNAPSHOT_PERIOD)
    return;

  timeCounter_ -= SNAPSHOT_PERIOD;
  for(SnapshotPtr snapshot : objects_)
    snapshot->accept(*this);
}

SnapshotPtr RadiusSensor::getSnapshot() const
{
  return SnapshotPtr(new SensorSnapshot(*this));
}

Physics::Mass RadiusSensor::getCurrentMass() const
{
  return Physics::Mass(1.0);
}

Physics::Force RadiusSensor::getCurrentForce() const
{
  return Physics::Force(Physics::Vector3(0, 0, 0));
}

bool RadiusSensor::isInRange(Snapshot& object)
{
  double dist = object.getPosition().distance(pos);
  return (dist <= range_ && dist >= 0.01); //TODO avoid magic const
}

DB::DynDBDriver dbDriver("./options.xml"); //FIXME sapoifasaaspofasjofpoaspof

void RadiusSensor::visit(CarSnapshot& car)
{
  if(!isInRange(car))
    return;

  Physics::GeoCoords geo(car.getPosition());
  dbDriver.insertDR(DB::DynDBDriver::DR_row(id_,
                                            -1,
                                            geo.lon,
                                            geo.lat,
                                            geo.mos,
                                            0,
                                            timer_->getDBTime()));

  std::cout << "I (id = " << id_ << ") see car in: "
            << geo.lon << ", "
            << geo.lat << ", "
            << geo.mos << "."
            << " Time: " << timer_->getDBTime()
            << std::endl;
}

void RadiusSensor::visit(PedestrianSnapshot& pedestrian)
{
  if(!isInRange(pedestrian))
    return;

  Physics::GeoCoords geo(pedestrian.getPosition());
  dbDriver.insertDR(DB::DynDBDriver::DR_row(id_,
                                            -1,
                                            geo.lon,
                                            geo.lat,
                                            geo.mos,
                                            0,
                                            timer_->getDBTime()));

  std::cout << "I (id = " << id_ << ") see pedestrian in: "
            << geo.lon << ", "
            << geo.lat << ", "
            << geo.mos << "."
            << " Time: " << timer_->getDBTime()
            << std::endl;
}

void RadiusSensor::visit(SensorSnapshot& snapshot)
{
  if(!isInRange(snapshot))
    return;

  Physics::GeoCoords geo(snapshot.getPosition());

  std::cout << "I see camera in: "
            << geo.lon << ", "
            << geo.lat << ", "
            << geo.mos << "."
            << " Time: " << timer_->getDBTime()
            << std::endl;
}

double RadiusSensor::getRange() const
{
  return range_;
}

}//namesapce Objects
}//namespace SimCity
}//namespace Model

