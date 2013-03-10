#ifndef GLOBALLOGGER_H
#define GLOBALLOGGER_H
#include <boost/thread/mutex.hpp>

class GlobalLogger
{
public:
  void log(const std::string& type,
           const std::string& module,
           const std::string& text);

  static GlobalLogger& logger();


private:
  GlobalLogger();
  GlobalLogger(const GlobalLogger&);
  GlobalLogger& operator=(const GlobalLogger&);

private:
  boost::mutex mutex_;
};

#endif // GLOBALLOGGER_H
