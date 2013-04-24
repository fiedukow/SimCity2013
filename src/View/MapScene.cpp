#include "MapScene.h"
#include <View/GraphicsElements/Road.h>
#include <View/GraphicsElements/Car.h>
#include <View/GraphicsElements/Sensor.h>
#include <View/GraphicsElements/Pedestrian.h>
#include <Common/GlobalLogger.h>
#include <sstream>

namespace SimCity
{
namespace View
{
using namespace GraphicsElements;

MapScene::MapScene(Model::MapPtr map, QObject *parent) :
  QGraphicsScene(parent),
  moveableGroup_(NULL),
  pedestrianGroup_(NULL),
  sensorsGroup_(NULL),
  carsVisible_(true),
  sensorsVisible_(true),
  mapVisible_(true),
  pedestrianVisible_(true)
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

  if(sensorsGroup_)
    removeItem(sensorsGroup_);
  delete sensorsGroup_;

  if(pedestrianGroup_)
    removeItem(pedestrianGroup_);
  delete pedestrianGroup_;

  moveableGroup_ = new QGraphicsItemGroup();
  pedestrianGroup_ = new QGraphicsItemGroup();
  sensorsGroup_ = new QGraphicsItemGroup();

  for(Model::Objects::SnapshotPtr& snapshot : snapshots)
    snapshot->accept(*this);

  moveableGroup_->setScale(mapSurface_->scale());
  sensorsGroup_->setScale(mapSurface_->scale());
  pedestrianGroup_->setScale(mapSurface_->scale());
  addItem(moveableGroup_);
  addItem(sensorsGroup_);
  addItem(pedestrianGroup_);
  setVisibility();
  Common::globLog("INF", "VIEW", "END");
}

void MapScene::setVisibility()
{
  if(moveableGroup_)
    moveableGroup_->setVisible(carsVisible_);
  if(pedestrianGroup_)
    pedestrianGroup_->setVisible(pedestrianVisible_);
  if(sensorsGroup_)
    sensorsGroup_->setVisible(sensorsVisible_);
  if(mapSurface_)
    mapSurface_->setVisible(mapVisible_);
}

void MapScene::visit(CarSnapshot& car)
{
  moveableGroup_->addToGroup(new Car(car,
                                     normVect_,
                                     moveableGroup_));
}

void MapScene::visit(PedestrianSnapshot& pedestrian)
{
  pedestrianGroup_->addToGroup(new Pedestrian(pedestrian,
                                              normVect_,
                                              pedestrianGroup_));
}

void MapScene::visit(SensorSnapshot& sensor)
{
  sensorsGroup_->addToGroup(new Sensor(sensor,
                                       normVect_,
                                       sensorsGroup_));
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

void MapScene::setMapVisible(bool visible)
{
  mapVisible_ = visible;
  setVisibility();
}

void MapScene::setCarsVisible(bool visible)
{
  carsVisible_ = visible;
  setVisibility();
}

void MapScene::setSensorsVisible(bool visible)
{
  sensorsVisible_ = visible;
  setVisibility();
}

void MapScene::setPedestriansVisible(bool visible)
{
  pedestrianVisible_ = visible;
  setVisibility();
}

}//namespace View
}//namespace SimCity
