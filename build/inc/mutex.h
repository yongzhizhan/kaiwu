//--------------------------------------------------------------------
#ifndef CPPREST_MUTEX_H
#define CPPREST_MUTEX_H
//--------------------------------------------------------------------
#include <pthread.h>
//--------------------------------------------------------------------
namespace kw {
//--------------------------------------------------------------------
class Mutex
{
public:
    Mutex()
    {
        pthread_mutex_init(&pthread_mutex_, 0);
    }

    ~Mutex()
    {
        pthread_mutex_destroy(&pthread_mutex_);
    }

    void Lock()
    {
        pthread_mutex_lock(&pthread_mutex_);
    }

    void UnLock()
    {
        pthread_mutex_unlock(&pthread_mutex_);
    }

    pthread_mutex_t* GetPThreadMutex()
    {
        return &pthread_mutex_;
    }

private:
    pthread_mutex_t pthread_mutex_;
};
//--------------------------------------------------------------------
class MutexGuard
{
public:
    MutexGuard(Mutex& mutex)
        :mutex_(mutex)
    {
        mutex_.Lock();
    }

    ~MutexGuard()
    {
        mutex_.UnLock();
    }

private:
    Mutex& mutex_;
};
//--------------------------------------------------------------------
#define MutexGuard(x) error "MutexGuard define as tempory object"
//--------------------------------------------------------------------
}
//--------------------------------------------------------------------
#endif // CPPREST_MUTEX_H
