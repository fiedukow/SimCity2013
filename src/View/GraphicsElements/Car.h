#ifndef CAR_H
#define CAR_H
#include <QGraphicsRectItem>
#include <Model/Objects/ObjectSnapshot.h>

namespace SimCity
{
namespace View
{
namespace GraphicsElements
{

class Car : public QGraphicsEllipseItem
{
public:
  Car(const Model::Objects::SnapshotPtr snapshot,
      const double* normalization,
      QGraphicsItem* parent = NULL);
};

}//namespace GraphicsElements
}//namespace View
}//namespace SimCity

#endif // ROAD_H
