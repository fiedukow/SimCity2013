#include "MapScene.h"
#include <View/GraphicsElements/Road.h>
#include <Common/GlobalLogger.h>
#include <sstream>

namespace SimCity
{
namespace View
{
using namespace GraphicsElements;

MapScene::MapScene(Model::MapPtr map, QObject *parent) :
  QGraphicsScene(parent)
{
  mapSurface_ = new QGraphicsItemGroup();
  for(const Model::StreetPtr& street : map->edges)
    mapSurface_->addToGroup(new Road(street,
                                     map->normalizationVector,
                                     mapSurface_));
  addItem(mapSurface_);
  mapSurface_->setScale(0.1);
  setSceneRect(0,
               0,
               mapSurface_->boundingRect().width() * 0.1,
               mapSurface_->boundingRect().height() * 0.1);
}

void MapScene::scalePlus()
{
  double newScale = mapSurface_->scale() * 1.2;
  mapSurface_->setScale(newScale);
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
  ss << "Setting (-) new scale to " << mapSurface_->scale();
  Common::globLog("INF", "VIEW", ss.str());
  setSceneRect(0,
               0,
               mapSurface_->boundingRect().width() * newScale,
               mapSurface_->boundingRect().height() * newScale);
}

}//namespace View
}//namespace SimCity
