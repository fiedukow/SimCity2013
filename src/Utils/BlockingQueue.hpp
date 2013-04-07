#ifndef BLOCKINGQUEUE_HPP
#define BLOCKINGQUEUE_HPP

#include <queue>
#include <deque>
#include <mutex>
#include <condition_variable>

namespace SimCity
{

template < class T, class Container = std::deque<T> >
class BlockingQueue
{
public:
  BlockingQueue()
  {}

  void push(const T& val)
  {
    std::unique_lock<std::mutex> lock(mutex_);
    queue_.push(val);
    condVar_.notify_one();
  }

  void pop(T& val)
  {
    std::unique_lock<std::mutex> lock(mutex_);
    condVar_.wait(lock,
                  [this]() -> bool
                  {
                    return !queue_.empty();
                  });
    std::swap(val, queue_.front());
    queue_.pop();
  }

private:
  std::queue<T, Container> queue_;
  std::mutex mutex_;
  std::condition_variable condVar_;
};

}//namespace SimCity

#endif // BLOCKINGQUEUE_HPP
