#include "StaticBaseDriver.h"
#include "Exceptions.h"

#include <iostream>
#include <sstream>

#include <pqxx/pqxx>

namespace SimCity
{
namespace Model
{

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

std::vector<StreetNode> StaticBaseDriver::getStreetNodes()
{
  ensureDBConnection();
  std::vector<StreetNode> result;
  std::string query("SELECT streetNodeId, lon, lat, mos FROM StreetNodes");
  pqxx::work t(*connection_);
  pqxx::result nodes = t.exec(query);
  for(const auto& node : nodes)
    result.push_back(StreetNode(node));

  disconnectIfNecessary();
  return result;
}

Map StaticBaseDriver::getMap()
{
  ensureDBConnection();
  std::vector<StreetNode> vertexes = getStreetNodes();
  std::vector<Street> edges;
  std::string query("SELECT firstNode, secondNode FROM Streets");
  pqxx::work t(*connection_);
  pqxx::result streets = t.exec(query);
  for(const auto& street : streets)
    edges.push_back(Street(street, vertexes));

  Map result(vertexes, edges);
  disconnectIfNecessary();
  return result;
}

bool StaticBaseDriver::ensureDBConnection()
{
  if(connection_ != NULL)
    return false;

  connect();
  return true;
}

bool StaticBaseDriver::disconnectIfNecessary()
{
  if(persistent_)
    return false;

  disconnect();
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
    //TODO throw my exception class.
  }
}

void StaticBaseDriver::disconnect()
{
  delete connection_;
  connection_ = NULL;
}

}//namespace Model
}//namespace SimCity
