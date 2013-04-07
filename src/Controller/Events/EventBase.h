#ifndef EVENTBASE_H
#define EVENTBASE_H
#include <memory>
#include <Utils/BlockingQueue.hpp>

namespace SimCity
{
namespace Controller
{

class Controller;

namespace Events
{

class EventBase
{
public:
  virtual ~EventBase();
  virtual void accept(Controller& visitor) = 0;
};

typedef std::shared_ptr<EventBase> EventBasePtr;
typedef BlockingQueue<Events::EventBasePtr> EventQueue;

}//namespace Events
}//namespace Controller
}//namespace SimCity

#endif // EVENTBASE_H
