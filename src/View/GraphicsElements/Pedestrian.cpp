#include "Pedestrian.h"
#include <cmath>

#include <QBrush>
#include <QColor>
#include <Model/Physics/Positioning.h>
#include <Common/GlobalLogger.h>
#include <Model/Objects/ObjectsSnapshots.h>
#include <sstream>

namespace SimCity
{
namespace View
{
namespace GraphicsElements
{

Pedestrian::Pedestrian(const Model::Objects::PedestrianSnapshot& obj,
         const double* normalization,
         QGraphicsItem* parent)
  : QGraphicsRectItem(parent)
{
  Model::Physics::Position pos = obj.getPosition();
  double x = pos.x - (normalization[0] * 111322.22222222222); //TODO avoid
  double y = pos.y - (normalization[1] * 111132.94444444445); //TODO avoid

  std::stringstream ss;
  ss << "X: " << x << " Y: " << y;
  Common::globLog("DBG", "VIEW", ss.str());
  if(obj.isMad())
    setBrush(QBrush(Qt::green));
  else
    setBrush(QBrush(Qt::yellow));
  double size = 10;
  setRect(0, 0, size, size); //TODO avoid magic const
  setPos(x-size/2,y-size/2);
}

}//namespace GraphicsElements
}//namespace View
}//namespace SimCity

