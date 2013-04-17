#ifndef MAPSCENE_H
#define MAPSCENE_H

#include <QGraphicsScene>
#include <Model/DBDataStructures.h>
#include <Model/Objects/ObjectSnapshot.h>

namespace SimCity
{
namespace View
{

using namespace Model::Objects;

class MapScene : public QGraphicsScene,
                 public SnapshotVisitor
{
  Q_OBJECT
public:
  explicit MapScene(Model::MapPtr map, QObject *parent = 0);
  virtual ~MapScene();
  void showNewMovable(Model::Objects::Snapshots snapshot);

  void visit(CarSnapshot& car);
  void visit(SensorSnapshot& sensor);

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
