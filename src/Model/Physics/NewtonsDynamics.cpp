#include "NewtonsDynamics.h"
#include <cmath>

namespace SimCity
{
namespace Model
{
namespace Physics
{

Vector3::Vector3(const double x, const double y, const double z)
  : x(x), y(y), z(z)
{}

Vector3 Vector3::operator*(double scalar) const
{
  return Vector3(x * scalar,
                 y * scalar,
                 z * scalar);
}

Vector3 Vector3::operator/(double scalar) const
{
  return Vector3(x / scalar,
                 y / scalar,
                 z / scalar);
}

double Vector3::length() const
{
  double result = sqrt(pow(x, 2) + pow(y, 2));
  result = sqrt(pow(result, 2) + pow(z, 2));
  return result;
}

Mass::Mass(const double value)
  : value(value)
{}

Force Mass::operator*(const Acceleration& acc) const
{
  return Force(acc.value * value);
}

Force::Force(const Vector3 value)
  : value(value)
{}

Acceleration Force::operator/(const Mass& mass) const
{
  return Acceleration(value / mass.value);
}

Mass Force::operator/(const Acceleration& acc) const
{
  return Mass(value.length() / acc.value.length());
}

Acceleration::Acceleration(const Vector3 value)
  : value(value)
{}

Force Acceleration::operator*(const Mass& mass) const
{
  return Force(value * mass.value);
}

Velocity Acceleration::operator*(const TimeDuration& dt) const
{
  return Velocity(value * dt.value);
}

TimeDuration::TimeDuration(const double value)
  : value(value)
{}

Shift TimeDuration::operator*(const Velocity& dt) const
{
  return Shift(dt.value * value);
}

Velocity TimeDuration::operator*(const Acceleration& acc) const
{
  return Velocity(acc.value * value);
}

Velocity::Velocity(const Vector3 value)
  : value(value)
{}

Velocity::Velocity(double x, double y, double z)
  : Velocity(Vector3(x, y, z))
{}

Velocity::Velocity(Acceleration acc, TimeDuration dt)
  : Velocity(acc * dt)
{}

Velocity Velocity::operator+(const Velocity& velocity) const
{
  return Velocity(value.x + velocity.value.x,
                  value.y + velocity.value.y,
                  value.z + velocity.value.z);
}

Shift::Shift(const Vector3 value)
  : value(value)
{}

Shift::Shift(double x, double y, double z)
  : Shift(Vector3(x, y, z))
{}

Shift::Shift(Acceleration acc, TimeDuration dt)
  : value((Shift(acc * dt * dt).value/2)) //at^2/2
{}

Shift::Shift(Velocity v, TimeDuration dt)
  : Shift(v * dt)
{}

Shift Velocity::operator*(const TimeDuration& dt) const
{
  return Shift(value * dt.value);
}

TimeDuration Velocity::operator/(const Acceleration& acc) const
{
  return TimeDuration(value.length() / acc.value.length());
}

Velocity Shift::operator/(const TimeDuration& dt) const
{
  return Velocity(value / dt.value);
}

TimeDuration Shift::operator/(const Velocity& dt) const
{
  return TimeDuration(value.length() / dt.value.length());
}

Shift Shift::operator+(const Shift& shift) const
{
  return Shift(value.x + shift.value.x,
               value.y + shift.value.y,
               value.z + shift.value.z);
}

Shift Shift::operator-(const Shift& shift) const
{
  return Shift(value.x - shift.value.x,
               value.y - shift.value.y,
               value.z - shift.value.z);
}

}//namespace Physics
}//namespace Model
}//namespace SimCity
