#ifndef PIPE_H
#define PIPE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class Pipe {
    std::queue<T> backend;
    std::mutex mtx;
    std::condition_variable not_empty;
    bool closed{false};
  public:
    Pipe& operator<<(T value) {
        // here we go!
        return *this;
    }
    
    Pipe& operator>>(T& value) {
        // here we go!
        return *this;
    }

    void close() {
        // here we go!
    }
    
    explicit operator bool() {
        // here we go!
    }
};
#endif
