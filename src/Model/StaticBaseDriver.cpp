#include "StaticBaseDriver.h"
#include "Exceptions.h"

#include <libpq-fe.h>

StaticBaseDriver::StaticBaseDriver(const char* connectionDetails,
                                   bool persistent)
  : connectionDetails_(connectionDetails),
    persistent_(persistent)
{
  if(persistent_)
    connect();
}

StaticBaseDriver::~StaticBaseDriver()
{
  if(persistent_)
    disconnect();
}

void StaticBaseDriver::connect()
{
  connection_ = PQconnectdb(connectionDetails_.c_str());
  if(connection_ == NULL)
    throw GeneralException("Unable to connect.");
  //connected
}

void StaticBaseDriver::disconnect()
{

}
