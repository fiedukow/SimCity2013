#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H
#include <QGraphicsRectItem>
#include <Model/Objects/ObjectSnapshot.h>

namespace SimCity
{
namespace View
{
namespace GraphicsElements
{

class Pedestrian : public QGraphicsRectItem
{
public:
  Pedestrian(const Model::Objects::PedestrianSnapshot& snapshot,
      const double* normalization,
      QGraphicsItem* parent = NULL);
};

}//namespace GraphicsElements
}//namespace View
}//namespace SimCity

#endif // ROAD_H
