#ifndef KW_COUNT_DOWN_LATCH_H
#define KW_COUNT_DOWN_LATCH_H

#include "mutex.h"
#include "condition.h"

namespace kw
{

class CountDownLatch
{
public:
    CountDownLatch(int count);

    void Wait();
    bool Wait(const timespec &time);
    void CountDown();
    int GetCount();

private:
    int count_;
    Mutex mutex_;
    Condition condition_;
};

}

#endif // KW_COUNT_DOWN_LATCH_H
