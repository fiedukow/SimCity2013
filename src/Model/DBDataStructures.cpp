#include "DBDataStructures.h"
#include <algorithm>
#include <boost/bind.hpp>

namespace SimCity
{
namespace Model
{

StreetNode::StreetNode(pqxx::result::tuple tableRow)
  : nodeId(tableRow["streetnodeid"].as<int>()),
    lon(tableRow["lon"].as<double>()),
    lat(tableRow["lat"].as<double>()),
    mos(tableRow["mos"].as<double>())
{
}

Street::Street(pqxx::result::tuple tableRow,
               const StreetNodes& vertexes)
  : first(NULL),
    second(NULL)
{
  int id[2] = { tableRow["firstNode" ].as<int>(),
                tableRow["secondNode"].as<int>() };

  first = *std::find_if(vertexes.begin(),
                        vertexes.end(),
                        [&id](const StreetNodePtr& ref) -> bool
                        {
                          return ref->nodeId == id[0];
                        });

  second = *std::find_if(vertexes.begin(),
                         vertexes.end(),
                         [&id](const StreetNodePtr& ref) -> bool
                         {
                           return ref->nodeId == id[1];
                         });
}

Map::Map(const StreetNodes &vertexes, Streets &edges)
  : vertexes(vertexes),
    edges(edges)
{
  double minX = 360, minY = 360;
  for(StreetNodePtr& node : this->vertexes)
  {
    minX = std::min(node->lon.get(), minX);
    minY = std::min(node->lat.get(), minY);
  }
  normalizationVector[0] = minX;
  normalizationVector[1] = minY;
}

Sensor::Sensor(pqxx::result::tuple tableRow)
  : sensorId(tableRow["sensorId"].as<unsigned int>()),
    lon(tableRow["lon"].as<double>()),
    lat(tableRow["lat"].as<double>()),
    mos(tableRow["mos"].as<double>()),
    range(tableRow["range"].as<double>())
{}

Streets Map::streetsInVertex(StreetNodePtr vertex)
{
  Streets result;
  for(const StreetPtr& street : edges)
    if(street->first == vertex || street->second == vertex)
      result.push_back(street);

  return result;
}

}//namespace Model
}//namespace SimCity

