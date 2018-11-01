#include "workQueue.h"

WorkQueue::WorkQueue(unsigned int _size)
{
    size = _size;
}

WorkQueue::~WorkQueue()
{
}

void WorkQueue::push(WorkPacket workPacket)
{
    std::unique_lock<std::mutex> lock(mx);
    notFullCv.wait(lock, [this] { return queue.size() < size; });

    queue.push(workPacket);
    notEmptyCv.notify_one();
}

WorkPacket WorkQueue::pop()
{
    std::unique_lock<std::mutex> lock(mx);
    notEmptyCv.wait(lock, [this] { return queue.size(); });

    WorkPacket ret{queue.front()};
    queue.pop();
    notFullCv.notify_one();

    return ret;
}