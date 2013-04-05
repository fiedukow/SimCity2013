#ifndef CONSTRAINEDNUMERIC_HPP
#define CONSTRAINEDNUMERIC_HPP

#include <ostream>

/**
 * Class for numeric type (comparable with double)
 * with valid values definable by bounds (min value, max value).
 * This class defines possibility
 */
template<int min, int max, typename Type = double>
class ConstrainedNumeric
{
public:
  ConstrainedNumeric(Type v)
    : v_(v)
  {
    ensureConstraint();
  }

  ConstrainedNumeric<min,max,Type>
    operator+(const ConstrainedNumeric<min,max,Type>& toAdd) const
  {
    return ConstrainedNumeric<min,max,Type>(v_ + toAdd.v_);
  }

  ConstrainedNumeric<min,max,Type>
    operator-(const ConstrainedNumeric<min,max,Type>& toAdd) const
  {
    return ConstrainedNumeric<min,max,Type>(v_ - toAdd.v_);
  }

  ConstrainedNumeric<min,max,Type>
    operator*(const ConstrainedNumeric<min,max,Type>& toAdd) const
  {
    return ConstrainedNumeric<min,max,Type>(v_ * toAdd.v_);
  }

  ConstrainedNumeric<min,max,Type>
    operator/(const ConstrainedNumeric<min,max,Type>& toAdd) const
  {
    return ConstrainedNumeric<min,max,Type>(v_ / toAdd.v_);
  }

  void ensureConstraint()
  {
    if(v_ < min || v_ > max)
      throw OutOfBoundValueException<Type>(v_, min, max);
  }

  Type get() const
  {
    return v_;
  }

private:
  Type v_;

  template<int minIn, int maxIn, typename TypeIn>
  friend std::ostream& operator<<(std::ostream& out,
                                  const ConstrainedNumeric<minIn,
                                                           maxIn,
                                                           TypeIn>& val);
};

template<int min, int max, typename Type = double>
std::ostream& operator<<(std::ostream& out,
                         const ConstrainedNumeric<min, max, Type>& val)
{
  out << val.v_;
  return out;
}

#endif // CONSTRAINEDNUMERIC_HPP
