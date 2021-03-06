#ifndef PIPE_H
#define PIPE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <future>

template <typename T>
class Pipe
{
    std::queue<T> backend;
    std::mutex mtx;
    std::condition_variable not_empty;
    bool closed{false};
    int latency;

  public:
    Pipe &operator<<(T value)
    {
        auto fut {async(&Pipe::writeIntoQueue, this, value)};
        return *this;
    }

    Pipe &operator>>(T &value)
    {
        if (closed == true)
        {
            return *this;
        }

        std::unique_lock lck(mtx);
        not_empty.wait(lck, [&] { return backend.size() > 0; });
        value = backend.front();
        backend.pop();

        return *this;
    }

    void close()
    {
        closed = true;
    }

    explicit operator bool()
    {
        return !closed;
    }

    void setLatency(int _latency)
    {
        latency = _latency;
    }

    void writeIntoQueue(long value) {
        this_thread::sleep_for(chrono::seconds(latency));
        std::unique_lock lck(mtx);
        backend.push(value);
        not_empty.notify_one();
    }
};
#endif
