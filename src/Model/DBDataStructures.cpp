#include "DBDataStructures.h"

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

}//namespace Model
}//namespace SimCity

