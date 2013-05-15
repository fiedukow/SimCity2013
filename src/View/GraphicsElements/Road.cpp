#include "Road.h"
#include <cmath>

#include <QBrush>
#include <QColor>
#include <QPen>
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
  : QGraphicsLineItem(parent)
{
  //TODO find better solution for converting etc
  double x[2] = { (street->first->lon.get()  - normalization[0]) * 111322.22222222222, //TODO avoid
                  (street->second->lon.get() - normalization[0]) * 111322.22222222222 }; //TODO avoid
  double y[2] = { (street->first->lat.get()  - normalization[1]) * 111132.94444444445, //TODO avoid
                  (street->second->lat.get() - normalization[1]) * 111132.94444444445 }; //TODO avoid
  setLine(x[0], y[0], x[1], y[1]);
  setPen(QPen(Qt::gray));
}

void Road::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
  std::stringstream ss;
  ss << "Bounding rect is in " << boundingRect().x()
     << ", " << boundingRect().y();
  Common::globLog("NOT", "VIEW", ss.str());
  QGraphicsLineItem::mousePressEvent(event);
}

}//namespace GraphicsElements
}//namespace View
}//namespace SimCity

