#include "MapScene.h"
#include <View/GraphicsElements/Road.h>
#include <View/GraphicsElements/Car.h>
#include <View/GraphicsElements/Sensor.h>
#include <Common/GlobalLogger.h>
#include <sstream>

namespace SimCity
{
namespace View
{
using namespace GraphicsElements;

MapScene::MapScene(Model::MapPtr map, QObject *parent) :
  QGraphicsScene(parent),
  moveableGroup_(NULL)
{
  mapSurface_ = new QGraphicsItemGroup();
  normVect_ = map->normalizationVector;
  for(const Model::StreetPtr& street : map->edges)
    mapSurface_->addToGroup(new Road(street,
                                     normVect_,
                                     mapSurface_));
  addItem(mapSurface_);
  mapSurface_->setScale(0.1);
  setSceneRect(0,
               0,
               mapSurface_->boundingRect().width() * 0.1,
               mapSurface_->boundingRect().height() * 0.1);
}

MapScene::~MapScene()
{}

void MapScene::showNewMovable(Model::Objects::Snapshots snapshots)
{
  if(moveableGroup_)
    removeItem(moveableGroup_);
  delete moveableGroup_;

  moveableGroup_ = new QGraphicsItemGroup();

  for(Model::Objects::SnapshotPtr& snapshot : snapshots)
    snapshot->accept(*this);

  moveableGroup_->setScale(mapSurface_->scale());
  addItem(moveableGroup_);
  Common::globLog("INF", "VIEW", "END");
}


void MapScene::visit(CarSnapshot& car)
{
  moveableGroup_->addToGroup(new Car(car, normVect_, moveableGroup_));
}

void MapScene::visit(SensorSnapshot& sensor)
{
  moveableGroup_->addToGroup(new Sensor(sensor, normVect_, moveableGroup_));
}

void MapScene::scalePlus()
{
  double newScale = mapSurface_->scale() * 1.2;
  mapSurface_->setScale(newScale);
  moveableGroup_->setScale(newScale);
  std::stringstream ss;
  ss << "Setting (-) new scale to " << mapSurface_->scale();
  Common::globLog("INF", "VIEW", ss.str());
  setSceneRect(0,
               0,
               mapSurface_->boundingRect().width() * newScale,
               mapSurface_->boundingRect().height() * newScale);
}

void MapScene::scaleMinus()
{
  double newScale = mapSurface_->scale() / 1.2;
  if(newScale < 0.001)
    newScale = 0.001;

  std::stringstream ss;
  mapSurface_->setScale(newScale);
  moveableGroup_->setScale(newScale);
  ss << "Setting (-) new scale to " << mapSurface_->scale();
  Common::globLog("INF", "VIEW", ss.str());
  setSceneRect(0,
               0,
               mapSurface_->boundingRect().width()  * newScale,
               mapSurface_->boundingRect().height() * newScale);
}

}//namespace View
}//namespace SimCity
