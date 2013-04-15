#include "Road.h"
#include <cmath>

#include <QBrush>
#include <QColor>
#include <Common/GlobalLogger.h>
#include <sstream>

namespace SimCity
{
namespace View
{
namespace GraphicsElements
{

Road::Road(const Model::StreetPtr& street,
           const double* normalization,
           QGraphicsItem* parent)
  : QGraphicsRectItem(parent)
{
  //TODO find better solution for converting etc
  double x[2] = { (street->first->lon.get()  - normalization[0]) * 111322.22222222222,
                  (street->second->lon.get() - normalization[0]) * 111322.22222222222 };
  double y[2] = { (street->first->lat.get()  - normalization[1]) * 111132.94444444445,
                  (street->second->lat.get() - normalization[1]) * 111132.94444444445 };
  double length = sqrt(pow(x[0]-x[1], 2) + pow(y[0]-y[1], 2));
  double rotation = atan((y[0] - y[1]) / (x[0] - x[1]));
  setRect(0, 0, length, 2.5);
  setRotation((rotation * 360) / (2 * M_PI));
  setPos(x[0], y[0]);
  setBrush(QBrush(Qt::gray));
}

void Road::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
  std::stringstream ss;
  ss << "Bounding rect is in " << boundingRect().x()
     << ", " << boundingRect().y();
  Common::globLog("NOT", "VIEW", ss.str());
  QGraphicsRectItem::mousePressEvent(event);
}

}//namespace GraphicsElements
}//namespace View
}//namespace SimCity

