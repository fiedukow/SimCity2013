#include "Exceptions.h"

GeneralException::GeneralException(const char* whatText)
  : whatText_(whatText)
{
}

const char* GeneralException::what() const throw()
{
  return whatText_.c_str();
}
