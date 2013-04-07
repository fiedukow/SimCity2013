#ifndef DBDATASTRUCTURES_H
#define DBDATASTRUCTURES_H
#include <Model/Exceptions.h>
#include <Model/ConstrainedNumeric.hpp>
#include <pqxx/pqxx>

#include <set>
#include <vector>
#include <memory>

namespace SimCity
{
namespace Model
{
typedef ConstrainedNumeric<-180, 180> Longitude;
typedef ConstrainedNumeric<-90, 90> Latitude;
typedef ConstrainedNumeric<-420, 8850> MetersOverSea;

struct StreetNode
{
  StreetNode(pqxx::result::tuple tableRow);

  int nodeId;
  Longitude lon;
  Latitude lat;
  MetersOverSea mos;
};

struct Street
{
  Street(pqxx::result::tuple tableRow,
         const std::vector<StreetNode>& vertexes); //TODO use std::set here

  const StreetNode* first;
  const StreetNode* second;
};

struct Map
{
  Map(const std::vector<StreetNode>& vertexes, std::vector<Street>& edges);

  std::vector<StreetNode> vertexes; //TODO use std::set here
  std::vector<Street>     edges;
};

typedef std::shared_ptr<Map> MapPtr;

}//namespace Model
}//namespace SimCity

#endif // DBDATASTRUCTURES_H
