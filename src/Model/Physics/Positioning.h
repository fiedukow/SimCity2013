#ifndef POSITIONING_H
#define POSITIONING_H
#include <Model/Physics/NewtonsDynamics.h>

namespace SimCity
{
namespace Model
{
namespace Physics
{

struct GeoCoords;
struct Shift;

struct Position
{
  Position(const GeoCoords& coords);
  Position(double x, double y, double z = 0);

  Position operator+(const Shift& shift) const;

  double x;
  double y;
  double z;

  const static double mPerLonDegree;
  const static double mPerLatDegree;
};

struct GeoCoords
{
  GeoCoords(double lon, double lat, double mos = 0);

  double lon;
  double lat;
  double mos;
};

}//namespace Model
}//namespace SimCity2013
}//namesapce Physics

#endif // POSITIONING_H
