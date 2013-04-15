#include "StaticBaseDriver.h"
#include "Exceptions.h"

#include <iostream>
#include <sstream>

#include <pqxx/pqxx>

#include <Common/GlobalLogger.h>

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

StreetNodes StaticBaseDriver::getStreetNodes()
{
  Common::globLog("NOT", "DBDri", "Reading nodes from DB...");
  ensureDBConnection();
  StreetNodes result;
  std::string query("SELECT streetNodeId, lon, lat, mos FROM StreetNodes");
  pqxx::work t(*connection_);
  pqxx::result nodes = t.exec(query);
  for(const auto& node : nodes)
    result.push_back(StreetNodePtr(new StreetNode(node)));

  disconnectIfNecessary();
  Common::globLog("NOT", "DBDri", "Finished reading nodes.");
  return result;
}

MapPtr StaticBaseDriver::getMap()
{
  Common::globLog("NOT", "DBDri", "Reading whole map from DB...");
  ensureDBConnection();
  StreetNodes vertexes = getStreetNodes();
  Streets edges; //TODO move getEdges to separedted method
  std::string query("SELECT firstNode, secondNode FROM Streets");
  pqxx::work t(*connection_);
  pqxx::result streets = t.exec(query);
  for(const auto& street : streets)
    edges.push_back(StreetPtr(new Street(street, vertexes)));

  MapPtr result(new Map(vertexes, edges));
  disconnectIfNecessary();
  Common::globLog("NOT", "DBDri", "Finished reading whole map.");
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
  Common::globLog("NOT", "DBDri", "Trying to connect to DB...");
  try
  {
    connection_ = new pqxx::connection(connectionDetails_);
  }
  catch(std::exception& e)
  {
    std::stringstream ss;
    ss << "Unable to connect to DB due to the exception:" << std::endl
       << e.what();
    Common::globLog("ERR", "DBDri", ss.str());
    connection_ = NULL;
  }
  Common::globLog("NOT", "DBDri", "Connected to DB.");
}

void StaticBaseDriver::disconnect()
{
  delete connection_;
  connection_ = NULL;
  Common::globLog("NOT", "DBDri", "Disconnected from DB.");
}

}//namespace Model
}//namespace SimCity
