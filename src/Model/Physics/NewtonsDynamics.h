#ifndef NEWTONSDYNAMICS_H
#define NEWTONSDYNAMICS_H

namespace SimCity
{
namespace Model
{
namespace Physics
{

struct Vector3
{
  Vector3 operator*(double scalar) const;
  Vector3 operator/(double scalar) const;
  double length() const;

  double x, y, z;
};

struct Mass;
struct Acceleration;
struct Force;

struct Mass
{
  Force operator*(const Acceleration& acc) const;
  double value;
};

struct Force
{
  Acceleration operator/(const Mass& mass) const;
  Mass operator/(const Acceleration& acc) const;
  Vector3 value;
};

struct Acceleration
{
  /**
   * @brief operator* F = ma => F = a*m
   * @param Mass
   * @return Force
   * Multiplies acceleration vector by mass to get force.
   */
  Force operator*(const Mass& mass) const;
  Vector3 value;
};

}//namespace Physics
}//namespace Model
}//namespace SimCity

#endif // NEWTONSDYNAMICS_H
