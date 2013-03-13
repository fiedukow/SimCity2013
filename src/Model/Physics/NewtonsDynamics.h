#ifndef NEWTONSDYNAMICS_H
#define NEWTONSDYNAMICS_H

namespace SimCity
{
namespace Model
{
namespace Physics
{

struct Mass;
struct Acceleration;
struct Force;
struct TimeDuration;
struct Shift;
struct Velocity;


/**
 *  --------------------------------------
 *  |     Phisical units used here       |
 *  --------------------------------------
 *  | Force          |   newtons         |
 *  | Mass           |   kilograms       |
 *  | Acceleration   |   meters/second^2 |
 *  | Time duration  |   seconds         |
 *  | Velocity       |   meter/second    |
 *  --------------------------------------
 *
 *  Implemented :
 *    F = ma
 *    s = vt
 *    v = at
 */

struct Vector3
{
  Vector3 operator*(double scalar) const;
  Vector3 operator/(double scalar) const;
  double length() const;

  double x, y, z;
};

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
  Velocity operator*(const TimeDuration& dt) const;

  Vector3 value;
};

struct TimeDuration
{
  Shift operator*(const Velocity& dt) const;
  Velocity operator*(const Acceleration& acc) const;

  double value;
};

struct Velocity
{
  Shift operator*(const TimeDuration& dt) const;
  TimeDuration operator/(const Acceleration& acc) const;

  double value;
};

struct Shift
{
  Velocity operator/(const TimeDuration& dt) const;
  TimeDuration operator/(const Velocity& dt) const;

  Vector3 value;
};

}//namespace Physics
}//namespace Model
}//namespace SimCity

#endif // NEWTONSDYNAMICS_H
