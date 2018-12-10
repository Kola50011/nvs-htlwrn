#pragma once

#include <mutex>
#include <queue>
#include <condition_variable>

class ResultQueue
{
  private:
    std::queue<double> queue;
    std::mutex mtx;
    std::condition_variable cv;

  public:
    ResultQueue(){};
    ~ResultQueue(){};

    void put(double num)
    {
        std::unique_lock lck{mtx};
        queue.push(num);
        cv.notify_one();
    };

    double take()
    {
        std::unique_lock lck{mtx};
        cv.wait(lck, [&] { return queue.size() > 0; });
        double ret{queue.front()};
        queue.pop();
        return ret;
    };
};
