/**
 * @author Maciej 'mac' Grzybek <mashester@gmail.com>
 * This part of code comes from repository authored by Maciej Grzybek and
 * available on github: https://github.com/maciejgrzybek/track0matic.
 * It is used with its author knowledge and acceptance.
 */

#include "logger.h"

#include <ctime>
#include <iostream>
#include <mutex>
#include <sstream>

namespace Common
{

GlobalLogger& GlobalLogger::getInstance()
{
  static GlobalLogger instance;
  return instance;
}

GlobalLogger& GlobalLogger::log(const std::string& module,
                                const std::string& msg)
{
  std::lock_guard<std::mutex> lock(mutex_);
  if (agent_)
    agent_->log(module,msg);

  return *this;
}

void GlobalLogger::setAgent(std::unique_ptr<LoggerAgent> agent)
{
  agent_ = std::move(agent);
}

std::string LoggerAgent::getCurrentTime() const
{
  time_t now = time(0);
  tm* localtm = localtime(&now);
  std::stringstream s;
  s << localtm->tm_mday
    << "-" << localtm->tm_mon+1
    << "-" << localtm->tm_year+1900
    << " "
    << localtm->tm_hour
    << ":" << localtm->tm_min
    << ":" << localtm->tm_sec;
  return s.str();
}

LoggerAgent& ConsoleLoggerAgent::log(const std::string& module,
                                     const std::string& msg)
{
  std::cout << getCurrentTime()
            << " " << module
            << ": " << msg << std::endl;

  return *this;
}

} // namespace Common
