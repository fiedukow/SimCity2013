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
  void visit(PedestrianSnapshot& pedestrian);
  void visit(SensorSnapshot& sensor);
  void setVisibility();

signals:

public slots:
  void scalePlus();
  void scaleMinus();
  void setMapVisible(bool visible);
  void setCarsVisible(bool visible);
  void setSensorsVisible(bool visible);
  void setPedestriansVisible(bool visible);

private:
  QGraphicsItemGroup* mapSurface_;
  double* normVect_;
  QGraphicsItemGroup* moveableGroup_;
  QGraphicsItemGroup* pedestrianGroup_;
  QGraphicsItemGroup* sensorsGroup_;

  bool carsVisible_;
  bool sensorsVisible_;
  bool mapVisible_;
  bool pedestrianVisible_;
};

}//namespace View
}//namespace SimCity

#endif // MAPSCENE_H
