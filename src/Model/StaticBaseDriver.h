#ifndef STATICBASEDRIVER_H
#define STATICBASEDRIVER_H

#include <string>
#include <libpq-fe.h>

class StaticBaseDriver
{
public:
  StaticBaseDriver(const char* connectionDetails = "",
                   bool persistent = true);
  ~StaticBaseDriver();
  void connect();
  void disconnect();

private:
  const std::string connectionDetails_;
  const bool persistent_;
  PGconn* connection_;
};

#endif // STATICBASEDRIVER_H
