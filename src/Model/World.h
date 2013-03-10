#ifndef WORLD_H
#define WORLD_H

#include <Model/SimulationPart.h>
#include <Model/DBDataStructures.h>

namespace SimCity
{
namespace Model
{

class World : public SimulationPart
{
public:
  World(const std::string& dbName,
        const std::string& dbUser,
        const std::string& dbPassword);
  virtual ~World();
  virtual void timePassed(uint ms);

  static Map readMapFromDB(const std::string& dbName,
                           const std::string& dbUser,
                           const std::string& dbPassword);

private:
  Map map_;
};

}//namespace Model
}//namespace SimCity

#endif // WORLD_H
