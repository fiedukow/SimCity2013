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

  void emitUpdateMap(const Model::Map*);

public slots:
  void start();
  void stop();
  void pause();

signals:
  void updateMap(const Model::Map*);
  //void updateState(const Snapshot);

private:
  Events::EventQueue& eventQueue_;
};

}//namespace Controller
}//namespace SimCity


#endif // QTUNSPAGHETTI_H
