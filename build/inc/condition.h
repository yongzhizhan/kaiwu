//----------------------------------------------------------------------------
#ifndef KW_CONDITION_H
#define KW_CONDITION_H
//----------------------------------------------------------------------------
#include <pthread.h>
#include <boost/noncopyable.hpp>
#include "mutex.h"
//----------------------------------------------------------------------------
namespace kw {
//----------------------------------------------------------------------------
class Condition : public boost::noncopyable
{
public:
    Condition()
    {
        pthread_cond_init(&cond_, 0);
    }

    ~Condition()
    {
        pthread_cond_destroy(&cond_);
    }

    int Wait(Mutex* mutex)
    {
        return pthread_cond_wait(&cond_, mutex->GetPThreadMutex());
    }

    int Wait(const timespec& wait_time, Mutex* mutex)
    {
        return pthread_cond_timedwait(&cond_, mutex->GetPThreadMutex(), &wait_time);
    }

    int Notify()
    {
        return pthread_cond_signal(&cond_);
    }

    int NotifyAll()
    {
        return pthread_cond_broadcast(&cond_);
    }

private:
    pthread_cond_t cond_;
};
//----------------------------------------------------------------------------
}
#endif // KW_CONDITION_H
