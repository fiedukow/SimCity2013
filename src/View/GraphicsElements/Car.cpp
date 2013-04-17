#include "Car.h"
#include <cmath>

#include <QBrush>
#include <QColor>
#include <Model/Physics/Positioning.h>
#include <Common/GlobalLogger.h>
#include <sstream>

namespace SimCity
{
namespace View
{
namespace GraphicsElements
{

Car::Car(const Model::Objects::SnapshotPtr obj,
         const double*,
         QGraphicsItem* parent)
  : QGraphicsEllipseItem(parent)
{
  Model::Physics::Position pos = obj->getPosition();
  double x = pos.x;// - (normalization[0] * 111322.22222222222);
  double y = pos.y;// - (normalization[1] * 111132.94444444445);

  std::stringstream ss;
  ss << "X: " << x << " Y: " << y;
  Common::globLog("DBG", "VIEW", ss.str());
  setBrush(QBrush(Qt::red));
  setRect(0, 0, 3, 3);
  setPos(x-1.5,y-1.5);

  /*double length = sqrt(pow(x[0]-x[1], 2) + pow(y[0]-y[1], 2));
  double rotation = atan((y[0] - y[1]) / (x[0] - x[1]));
  setRect(0, 0, length, 2.5);
  setRotation((rotation * 360) / (2 * M_PI));
  setPos(x[0], y[0]);
  setBrush(QBrush(Qt::gray));*/
}

}//namespace GraphicsElements
}//namespace View
}//namespace SimCity

