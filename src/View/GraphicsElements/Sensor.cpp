#include "Sensor.h"
#include <cmath>

#include <QBrush>
#include <QColor>
#include <Model/Physics/Positioning.h>
#include <Common/GlobalLogger.h>
#include <Model/Objects/ObjectsSnapshots.h>
#include <sstream>
#include <QPen>

namespace SimCity
{
namespace View
{
namespace GraphicsElements
{

Sensor::Sensor(const Model::Objects::SensorSnapshot& obj,
               const double* normalization,
               QGraphicsItem* parent)
  : QGraphicsEllipseItem(parent)
{
  Model::Physics::Position pos = obj.getPosition();
  double x = pos.x - (normalization[0] * 111322.22222222222);
  double y = pos.y - (normalization[1] * 111132.94444444445);

  std::stringstream ss;
  ss << "X: " << x << " Y: " << y;
  Common::globLog("DBG", "VIEW", ss.str());
  setBrush(QBrush(QColor(255,255,102,128)));
  setPen(QPen(QColor(255,255,0)));
  double size = obj.getRange()*2;
  setRect(0, 0, size, size); //TODO avoid magic const
  setPos(x-size/2,y-size/2);
  setZValue(1.0);
}

}//namespace GraphicsElements
}//namespace View
}//namespace SimCity

