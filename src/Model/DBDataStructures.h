#ifndef DBDATASTRUCTURES_H
#define DBDATASTRUCTURES_H
#include <Model/Exceptions.h>
#include <Model/ConstrainedNumeric.hpp>
#include <pqxx/pqxx>

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

}//namespace Model
}//namespace SimCity

#endif // DBDATASTRUCTURES_H
