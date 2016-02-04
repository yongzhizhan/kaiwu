#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <deque>
#include <vector>
#include <tr1/memory>
#include <tr1/functional>
#include "condition.h"
#include "mutex.h"
#include "thread.h"
#include "string_arg.h"

namespace kw
{

class ThreadPool
{
public:
    typedef std::tr1::function<void()> ThreadTask;
    typedef std::deque<ThreadTask> TaskDeque;
    typedef std::vector<Thread*> ThreadVector;

public:
    ThreadPool(int thread_count, StringArg thread_pool_name = "thread_pool");
    ~ThreadPool();

    bool Start();
    bool Stop();

    bool Run(ThreadTask task);

private:
    void Loop();

private:
    TaskDeque tasks_;
    ThreadVector threads_;
    Mutex mutex_;
    Condition condition_;
    int thread_count_;
    bool quit_;
};

}
#endif // THREAD_POOL_H
