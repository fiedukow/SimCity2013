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
  Vector3(const double x, const double y, const double z);

  Vector3 operator*(double scalar) const;
  Vector3 operator/(double scalar) const;
  double length() const;

  double x, y, z;
};

struct Mass
{
  Mass(const double value);

  Force operator*(const Acceleration& acc) const;

  double value;
};

struct Force
{
  Force(const Vector3 value);

  Acceleration operator/(const Mass& mass) const;
  Mass operator/(const Acceleration& acc) const;

  Vector3 value;
};

struct Acceleration
{
  Acceleration(const Vector3 value);

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
  TimeDuration(const double value);

  Shift operator*(const Velocity& dt) const;
  Velocity operator*(const Acceleration& acc) const;

  double value;
};

struct Velocity
{
  Velocity(const Vector3 value);
  Velocity(double x, double y, double z);
  Velocity(Acceleration acc, TimeDuration dt);

  Shift operator*(const TimeDuration& dt) const;
  TimeDuration operator/(const Acceleration& acc) const;
  Velocity operator+(const Velocity& shift) const;

  Vector3 value;
};

struct Shift
{
  Shift(const Vector3 value);
  Shift(double x, double y, double z);
  Shift(Acceleration acc, TimeDuration dt);
  Shift(Velocity v, TimeDuration dt);

  Velocity operator/(const TimeDuration& dt) const;
  TimeDuration operator/(const Velocity& dt) const;
  Shift operator+(const Shift& shift) const;
  Shift operator-(const Shift& shift) const;

  Vector3 value;
};

}//namespace Physics
}//namespace Model
}//namespace SimCity

#endif // NEWTONSDYNAMICS_H
