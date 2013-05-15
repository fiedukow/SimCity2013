/**
 * @author Maciej 'mac' Grzybek <mashester@gmail.com>
 * This part of code comes from repository authored by Maciej Grzybek and
 * available on github: https://github.com/maciejgrzybek/track0matic.
 * It is used with its author knowledge and acceptance.
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <memory>
#include <mutex>
#include <string>

namespace Common
{

class LoggerAgent
{
public:
  // does not have to be thread safe, because upper layer will always secure it
  virtual LoggerAgent& log(const std::string& module,
                           const std::string& msg) = 0;

  virtual std::string getCurrentTime() const;
};

class ConsoleLoggerAgent : public LoggerAgent
{
public:
  virtual LoggerAgent& log(const std::string& module,
                           const std::string& msg);
};

class GlobalLogger
{
public:
  static GlobalLogger& getInstance();

  GlobalLogger& log(const std::string& module, const std::string& msg);
  void setAgent(std::unique_ptr<LoggerAgent> agent);

private:
  GlobalLogger() = default;
  ~GlobalLogger() = default;
  GlobalLogger(const GlobalLogger&) = delete;
  GlobalLogger& operator=(const GlobalLogger&) = delete;

  std::unique_ptr<LoggerAgent> agent_;
  std::mutex mutex_;
};

} // namespace Common

#endif // LOGGER_H

