#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class GeneralException : public std::exception
{
public:
  GeneralException(const char* whatText);
  virtual const char* what() const throw();

private:
  std::string whatText_;
};

#endif // EXCEPTIONS_H
