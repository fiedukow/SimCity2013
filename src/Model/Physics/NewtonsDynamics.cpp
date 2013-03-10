#include "NewtonsDynamics.h"
#include <cmath>

namespace SimCity
{
namespace Model
{
namespace Physics
{

Vector3 Vector3::operator*(double scalar) const
{
  Vector3 result;
  result.x = x * scalar;
  result.y = y * scalar;
  result.z = z * scalar;
  return result;
}

Vector3 Vector3::operator/(double scalar) const
{
  Vector3 result;
  result.x = x / scalar;
  result.y = y / scalar;
  result.z = z / scalar;
  return result;
}

double Vector3::length() const
{
  double result = sqrt(pow(x, 2) + pow(y, 2));
  result = sqrt(pow(result, 2) + pow(z, 2));
  return result;
}


Force Mass::operator*(const Acceleration& acc) const
{
  Force result;
  result.value = acc.value * value;
  return result;
}

Acceleration Force::operator/(const Mass& mass) const
{
  Acceleration result;
  result.value = value / mass.value;
  return result;
}

Mass Force::operator/(const Acceleration& acc) const
{
  Mass result;
  result.value = value.length()/acc.value.length();
  return result;
}

Force Acceleration::operator*(const Mass& mass) const
{
  Force result;
  result.value = value * mass.value;
  return result;
}

}//namespace Physics
}//namespace Model
}//namespace SimCity
