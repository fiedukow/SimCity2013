#include "Positioning.h"
#include <Model/Physics/NewtonsDynamics.h>
#include <cmath>

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
    y(coords.lat * mPerLatDegree),
    z(coords.mos)
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

Shift Position::operator-(const Position& pos) const
{
  return Shift(x - pos.x,
               y - pos.y,
               z - pos.z);
}

double Position::distance(const Position& pos) const
{
  double dx = std::abs(x - pos.x);
  double dy = std::abs(y - pos.y);
  double dz = std::abs(z - pos.z);
  double xy = sqrt(std::pow(dx, 2) + std::pow(dy, 2));

  return sqrt(std::pow(xy, 2) + std::pow(dz, 2));
}

Angle::Angle(double radians)
  : radians(radians)
{
  normalize();
}

Angle Angle::operator+(const Angle& toAdd) const
{
  return Angle(radians + toAdd.radians);
}

void Angle::normalize()
{
  while(radians > 2*M_PI)
    radians -= 2*M_PI;

  while(radians < 0)
    radians += 2*M_PI;
}

GeoCoords::GeoCoords(double lon, double lat, double mos)
  : lon(lon), lat(lat), mos(mos)
{}

GeoCoords::GeoCoords(const Position& pos)
  : lon(pos.x / Position::mPerLonDegree),
    lat(pos.y / Position::mPerLatDegree),
    mos(pos.z)
{}

}//namespace Model
}//namespace SimCity2013
}//namesapce Physics
