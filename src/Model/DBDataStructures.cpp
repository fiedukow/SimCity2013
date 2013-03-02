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
               const std::vector<StreetNode>& vertexes)
  : first(NULL),
    second(NULL)
{
  int id[2] = { tableRow["firstNode" ].as<int>(),
                tableRow["secondNode"].as<int>() };

  first = &*std::find_if(vertexes.begin(),
                         vertexes.end(),
                         [&id](const StreetNode& ref) -> bool
                         {
                           return ref.nodeId == id[0];
                         });

  second = &*std::find_if(vertexes.begin(),
                          vertexes.end(),
                          [&id](const StreetNode& ref) -> bool
                          {
                            return ref.nodeId == id[1];
                          });
}

Map::Map(const std::vector<StreetNode>& vertexes, std::vector<Street>& edges)
  : vertexes(vertexes),
    edges(edges)
{
}

}//namespace Model
}//namespace SimCity

