#ifndef MAPSCENE_H
#define MAPSCENE_H

#include <QGraphicsScene>
#include <Model/DBDataStructures.h>

namespace SimCity
{
namespace View
{

class MapScene : public QGraphicsScene
{
  Q_OBJECT
public:
  explicit MapScene(Model::MapPtr map, QObject *parent = 0);

signals:

public slots:

};

}//namespace View
}//namespace SimCity

#endif // MAPSCENE_H
