#ifndef SENSOR_H
#define SENSOR_H
#include <QGraphicsRectItem>
#include <Model/Objects/ObjectSnapshot.h>

namespace SimCity
{
namespace View
{
namespace GraphicsElements
{

class Sensor : public QGraphicsEllipseItem
{
public:
  Sensor(const Model::Objects::SensorSnapshot& snapshot,
         const double* normalization,
         QGraphicsItem* parent = NULL);
};

}//namespace GraphicsElements
}//namespace View
}//namespace SimCity

#endif // ROAD_H
