#ifndef QTUNSPAGHETTI_H
#define QTUNSPAGHETTI_H
#include <QObject>
#include <Model/DBDataStructures.h>
#include <Controller/Events/EventBase.h>

namespace SimCity
{
namespace Controller
{

class QtUnspaghetti : public QObject
{
  Q_OBJECT
public:
  QtUnspaghetti(Events::EventQueue& eventQueue);
  virtual ~QtUnspaghetti();

  void emitUpdateMap(const Model::MapPtr);
  Model::MapPtr getMapSnapshot();

public slots:
  void start();
  void stop();
  void pause();
  void requestNewMapSnapshot();

signals:
  void updateMap();
  //void updateState(const Snapshot);

private:
  Events::EventQueue& eventQueue_;
  Model::MapPtr currentMapPtr_;
};

}//namespace Controller
}//namespace SimCity


#endif // QTUNSPAGHETTI_H
