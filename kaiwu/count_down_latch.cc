#include "count_down_latch.h"

namespace kw
{

CountDownLatch::CountDownLatch(int count)
    :count_(count)
{
}

void CountDownLatch::Wait()
{
    MutexGuard guard(mutex_);
    if(0 == count_)
        return;

    condition_.Wait(&mutex_);
}

bool CountDownLatch::Wait(const timespec& time)
{
    MutexGuard guard(Mutex);
    if(0 == count_)
        return true;

    return (0 == condition_.Wait(time, &mutex_));
}

void CountDownLatch::CountDown()
{
    MutexGuard guard(Mutex);
    if(0 == count_)
        return;

    count_--;
    if(0 == count_)
        condition_.NotifyAll();
}

int CountDownLatch::GetCount()
{
    return count_;
}

}
