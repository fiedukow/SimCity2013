#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <Common/NewStateObserver.h>
#include <Utils/BlockingQueue.hpp>
#include <Controller/Events/AllEvents.h>
#include <Controller/QtUnspaghetti.h>
#include <Model/Model.h>

namespace boost
{
class thread;
}

namespace SimCity
{
namespace Controller
{
class Controller : public Common::NewStateObserver
{
public:
  Controller(QtUnspaghetti& qtControll,
             Events::EventQueue& eventQueue,
             Model::Model& model);
  virtual ~Controller();

  void operator()();

  virtual void notifyNewState();

  void visit(EventStop&);
  void visit(EventStart&);
  void visit(EventPause&);
  void visit(EventInterrupt&);
  void visit(EventNewMapRequest&);

private:
  void startThread();
  void stopThread();

private:
  QtUnspaghetti& qtControll_;
  Events::EventQueue& eventQueue_;
  Model::Model& model_;

  boost::thread* thread_;
  bool stopThread_;
};

}//namespace Controller
}//namespace SimCity

#endif // CONTROLLER_H

