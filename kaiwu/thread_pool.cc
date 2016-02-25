#include <stdio.h>
#include <sys/time.h>
#include "shared_lib.h"
#include "thread_pool.h"

namespace kw
{

ThreadPool::ThreadPool(int thread_count, StringArg thread_pool_name)
    :thread_count_(thread_count), quit_(false)
{
    for(int i=0; i<thread_count_; i++)
    {
        char buf[32];
        snprintf(buf, sizeof buf, "%s_%d", thread_pool_name.data(), i);

        Thread::ThreadFunc thread_func = std::tr1::bind(&ThreadPool::Loop, this);
        Thread* thread = new Thread(thread_func, buf);

        threads_.push_back(thread);
    }
}

ThreadPool::~ThreadPool()
{
    for(ThreadVector::iterator iter = threads_.begin(); threads_.end() != iter; ++iter)
    {
        Thread* thread = *(iter);
        delete thread;
    }
}

bool ThreadPool::Start()
{
    for(ThreadVector::iterator iter = threads_.begin(); threads_.end() != iter; ++iter)
    {
        Thread* thread = *(iter);
        thread->Start();
    }

    return true;
}

bool ThreadPool::Stop()
{
    quit_ = true;
    condition_.NotifyAll();

    for(ThreadVector::iterator iter = threads_.begin(); threads_.end() != iter; ++iter)
    {
        Thread* thread = *(iter);
        thread->Join();
    }

    return true;
}

bool ThreadPool::Run(ThreadTask task)
{
    {
        MutexGuard guard(mutex_);
        tasks_.push_back(task);
    }

    condition_.Notify();
    return true;
}

void ThreadPool::Loop()
{
    ThreadTask task;
    while(false == quit_)
    {
        {
            MutexGuard guard(mutex_);
            if(true == tasks_.empty())
            {
                timeval daytime;
                gettimeofday(&daytime, 0);

                timespec time;
                time.tv_sec = daytime.tv_sec + 1;
                time.tv_nsec = daytime.tv_usec * 1000;

                if(0 != condition_.Wait(time, &mutex_))
                    continue;
            }

            if(true == tasks_.empty())
                continue;

            task = tasks_.front();
            tasks_.pop_front();
        }

        task();
    }
}

}
