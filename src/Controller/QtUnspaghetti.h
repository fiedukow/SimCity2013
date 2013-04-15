#ifndef QTUNSPAGHETTI_H
#define QTUNSPAGHETTI_H
#include <QObject>
#include <Model/DBDataStructures.h>
#include <Controller/Events/EventBase.h>
#include <Model/Objects/ObjectSnapshot.h>

#include <QMutex>

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
  void emitUpdateSnapshot(const Model::Objects::Snapshots& snaps);
  Model::MapPtr getMapSnapshot();
  Model::Objects::Snapshots getSnapshots();

public slots:
  void start();
  void stop();
  void pause();
  void requestNewMapSnapshot();
  void requestSnapshot();

signals:
  void updateMap();
  void updateState();

private:
  Events::EventQueue& eventQueue_;
  Model::MapPtr currentMapPtr_;
  Model::Objects::Snapshots currentSnapshot_;
  QMutex oneWayLock_;
};

}//namespace Controller
}//namespace SimCity


#endif // QTUNSPAGHETTI_H
