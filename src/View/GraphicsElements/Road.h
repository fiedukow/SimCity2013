#ifndef ROAD_H
#define ROAD_H
#include <QGraphicsRectItem>
#include <Model/DBDataStructures.h>

namespace SimCity
{
namespace View
{
namespace GraphicsElements
{

class Road : public QGraphicsRectItem
{
public:
  Road(const Model::StreetPtr& street,
       const double* normalization,
       QGraphicsItem* parent = NULL);
};

}//namespace GraphicsElements
}//namespace View
}//namespace SimCity

#endif // ROAD_H
