#ifndef DBDATASTRUCTURES_H
#define DBDATASTRUCTURES_H
#include <Model/Exceptions.h>
#include <Model/ConstrainedNumeric.hpp>
#include <pqxx/pqxx>

#include <set>
#include <vector>
#include <memory>

namespace SimCity
{
namespace Model
{
typedef ConstrainedNumeric<-180, 180> Longitude;
typedef ConstrainedNumeric<-90, 90> Latitude;
typedef ConstrainedNumeric<-420, 8850> MetersOverSea;

struct StreetNode
{
  StreetNode(pqxx::result::tuple tableRow);

  int nodeId;
  Longitude lon;
  Latitude lat;
  MetersOverSea mos;
};

typedef std::shared_ptr<StreetNode> StreetNodePtr;
typedef std::vector<StreetNodePtr> StreetNodes;

struct Street
{
  Street(pqxx::result::tuple tableRow,
         const StreetNodes& vertexes);

  StreetNodePtr first;
  StreetNodePtr second;
};

typedef std::shared_ptr<Street> StreetPtr;
typedef std::vector<StreetPtr> Streets;

struct Map
{
  Map(const StreetNodes& vertexes, Streets& edges);
  Streets streetsInVertex(StreetNodePtr vertex);

  StreetNodes vertexes;
  Streets     edges;
  double      normalizationVector[2];
};

typedef std::shared_ptr<Map> MapPtr;

struct Sensor
{
  Sensor(pqxx::result::tuple tableRow);

  uint sensorId;
  Longitude lon;
  Latitude lat;
  MetersOverSea mos;
  double range;
};

typedef std::shared_ptr<Sensor> SensorPtr;
typedef std::vector<SensorPtr> Sensors;

}//namespace Model
}//namespace SimCity

#endif // DBDATASTRUCTURES_H
