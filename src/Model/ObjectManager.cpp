#include "ObjectManager.h"
#include <Common/GlobalLogger.h>

namespace SimCity
{
namespace Model
{

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::timePassed(uint ms)
{
  std::stringstream ss;
  ss << "moving forward by " << ms << "ms.";
  Common::globLog("NOT", "ObjMgr", ss.str());
  return;
}



}//namespace SimCity
}//namespace Model

