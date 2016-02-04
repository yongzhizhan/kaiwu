//--------------------------------------------------------------------
#include <stdio.h>
#include "thread_info.h"
#include "thread.h"
//--------------------------------------------------------------------
namespace kw {
//--------------------------------------------------------------------
class ThreadData
{
public:
    ThreadData(Thread::ThreadFunc func, std::string thread_name)
        :func_(func), thread_name_(thread_name.data())
    {
    }

    void RunInThread()
    {
        if(true != thread_name_.empty())
        {
            assert(sizeof thread_info::t_thread_name > thread_name_.length());
            strncpy(thread_info::t_thread_name, thread_name_.c_str(), sizeof thread_info::t_thread_name);
            thread_info::t_set_thread_name = true;
        }

        func_();
    }

private:
    Thread::ThreadFunc func_;
    std::string thread_name_;
};
//--------------------------------------------------------------------
Thread::Thread(ThreadFunc func, StringArg thread_name)
    :func_(func), thread_name_(thread_name.data()), tid_(0), started_(false)
{
}
//--------------------------------------------------------------------
Thread::~Thread()
{
}
//--------------------------------------------------------------------
bool Thread::Start()
{
    ThreadData* data = new ThreadData(func_, thread_name_);
    int result = pthread_create(&tid_, 0, &StartThread, data);
    if(0 != result)
    {
        printf("error:%d", result);
        return false;
    }

    started_ = true;

    return true;
}
//--------------------------------------------------------------------
void Thread::Join()
{
    if(0 == tid_)
        return;

    pthread_join(tid_, 0);

    started_ = false;
}
//--------------------------------------------------------------------
void* Thread::StartThread(void* data)
{
    ThreadData* thread_data = static_cast<ThreadData*>(data);
    thread_data->RunInThread();

    delete thread_data;

    return 0;
}
//--------------------------------------------------------------------
}
