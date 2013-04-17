#include "ObjectManager.h"
#include <Common/GlobalLogger.h>

namespace SimCity
{
namespace Model
{

ObjectManager::ObjectManager(WorldPtr world, uint limit)
  : world_(world),
    limit_(limit)
{}

ObjectManager::~ObjectManager()
{}

void ObjectManager::timePassed(uint ms)
{
  while(objects_.size() < limit_)
  {
  //  LiveObjectPtr newObject(new LiveObjectPtr)
  //  objects_.push_back();
  }
  std::stringstream ss;
  ss << "moving forward by " << ms << "ms.";
  Common::globLog("NOT", "ObjMgr", ss.str());
  return;
}



}//namespace SimCity
}//namespace Model

