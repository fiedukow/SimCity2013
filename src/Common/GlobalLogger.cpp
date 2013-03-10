#include "GlobalLogger.h"
#include <iostream>
#include <ctime>
#include <cassert>

void GlobalLogger::log(const std::string& type,
                       const std::string& module,
                       const std::string& text)
{
  time_t rawtime;
  time(&rawtime);
  std::string time = asctime(localtime(&rawtime));
  time = time.substr(0, time.length()-1);
  std::cout << time
            << " [" << type << "] "
            << module << ": "
            << text << std::endl;
}

GlobalLogger& GlobalLogger::logger()
{
  static GlobalLogger logger;
  return logger;
}

GlobalLogger::GlobalLogger()
{}
GlobalLogger::GlobalLogger(const GlobalLogger&)
{}
GlobalLogger& GlobalLogger::operator=(const GlobalLogger&)
{
  assert(false);
  return *this;
}
