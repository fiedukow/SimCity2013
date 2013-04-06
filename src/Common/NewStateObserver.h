#ifndef NEWSTATEOBSERVER_H
#define NEWSTATEOBSERVER_H

namespace SimCity
{
namespace Common
{

class NewStateObserver
{
public:
  virtual ~NewStateObserver();
  virtual void notifyNewState() = 0;
};

}//namespace Common
}//namespace SimCity

#endif // NEWSTATEOBSERVER_H
