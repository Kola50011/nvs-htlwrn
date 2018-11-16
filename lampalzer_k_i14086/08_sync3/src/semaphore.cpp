#include "semaphore.h"
#include <mutex>
#include "utils.h"

Semaphore::Semaphore(unsigned int _size) : size(_size)
{
}

Semaphore::Semaphore() : size{1}
{
}

Semaphore::~Semaphore()
{
}

int Semaphore::avaliblePermits() {
    return size;
}

void Semaphore::acquire() {
    std::unique_lock<std::mutex> lock(mtx);
    notEmpty.wait(lock, [this] { return size > 0; });
    size -= 1;
    Utils::println("Currently ", std::to_string(size), " left forks available");
}

void Semaphore::release() {
    std::unique_lock<std::mutex> lock(mtx);
    size += 1;
    Utils::println("Currently ", std::to_string(size), " left forks available");
    notEmpty.notify_one();
}