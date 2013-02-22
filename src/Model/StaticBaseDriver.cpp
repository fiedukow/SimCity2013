#include "StaticBaseDriver.h"
#include "Exceptions.h"

#include <iostream>

#include <pqxx/pqxx>

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
  disconnect();
}

bool StaticBaseDriver::ensureDBConnection()
{
  if(connection_ != NULL)
    return false;

  connect();
  return true;
}

void StaticBaseDriver::connect()
{
  try
  {
    connection_ = new pqxx::connection(connectionDetails_);
  }
  catch(std::exception& e)
  {
    std::cerr << "Unable to connect to DB due to the exception:" << std::endl
              << e.what() << std::endl;
    connection_ = NULL;
  }
}

void StaticBaseDriver::disconnect()
{
  delete connection_;
  connection_ = NULL;
}
