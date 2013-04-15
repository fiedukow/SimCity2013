#ifndef MAPSCENE_H
#define MAPSCENE_H

#include <QGraphicsScene>
#include <Model/DBDataStructures.h>
#include <Model/Objects/ObjectSnapshot.h>

namespace SimCity
{
namespace View
{

class MapScene : public QGraphicsScene
{
  Q_OBJECT
public:
  explicit MapScene(Model::MapPtr map, QObject *parent = 0);
  void showNewMovable(Model::Objects::Snapshots snapshot);

signals:

public slots:
  void scalePlus();
  void scaleMinus();

private:
  QGraphicsItemGroup* mapSurface_;
  QGraphicsRectItem* mapRect_;
  double* normVect_;
  QGraphicsItemGroup* moveableGroup_;
};

}//namespace View
}//namespace SimCity

#endif // MAPSCENE_H
