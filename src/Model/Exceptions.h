#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>
#include <sstream>

class GeneralException : public std::exception
{
public:
  GeneralException(const char* whatText);
  virtual const char* what() const throw();

private:
  std::string whatText_;
};

template<class Type>
class OutOfBoundValueException : public GeneralException
{
public:
  OutOfBoundValueException(Type value, int min, int max)
    : GeneralException(generateWhatText(value, min, max).c_str())
  {}

private:
  static std::string generateWhatText(Type value, int min, int max)
  {
    std::stringstream ss;
    ss << "The value " << value << " is not between "
       << min << " and " << max << std::endl;
    return ss.str();
  }
};

#endif // EXCEPTIONS_H
