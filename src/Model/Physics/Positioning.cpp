#include "Positioning.h"
#include <Model/Physics/NewtonsDynamics.h>

namespace SimCity
{
namespace Model
{
namespace Physics
{

const double Position::mPerLonDegree = 111322.22222222222;
const double Position::mPerLatDegree = 111132.94444444445;

Position::Position(const GeoCoords &coords)
  : x(coords.lon * mPerLonDegree),
    y(coords.lat * mPerLatDegree)
{}

Position::Position(double x, double y, double z)
  : x(x), y(y), z(z)
{}

Position Position::operator+(const Shift& shift) const
{
  return Position(x + shift.value.x,
                  y + shift.value.y,
                  z + shift.value.z);
}

Angle::Angle(double radians)
  : radians(radians)
{
  normalize();
}

Angle::operator+(const Angle& toAdd)
{
  return Angle(radians + toAdd.radians);
}

GeoCoords::GeoCoords(double lon, double lat, double mos)
  : lon(lon), lat(lat), mos(mos)
{}

}//namespace Model
}//namespace SimCity2013
}//namesapce Physics
