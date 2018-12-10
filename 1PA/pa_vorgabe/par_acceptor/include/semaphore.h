#include <condition_variable>
#include <mutex>

class Semaphore
{
  private:
    int free;
    std::mutex mtx;
    std::condition_variable cv;

  public:
    Semaphore(int amount) : free{amount} {};
    Semaphore() : free{1} {};
    ~Semaphore(){};

    void acquire(){
        std::unique_lock lck{mtx};
        cv.wait(lck, [&] {return free > 0;} );
        free -= 1;
    };

    void release(){
        std::unique_lock lck{mtx};
        free += 1;
        cv.notify_one();
    };
};