//--------------------------------------------------------------------
#ifndef KW_THREAD_H
#define KW_THREAD_H
//--------------------------------------------------------------------
#include <memory>
#include <tr1/functional>
#include <pthread.h>
#include "string_arg.h"
//--------------------------------------------------------------------
namespace kw{
//--------------------------------------------------------------------
class Thread
{
public:
    typedef std::tr1::function<void()> ThreadFunc;

    Thread(ThreadFunc func, StringArg thread_name="");
    ~Thread();

    bool Start();
    void Join();

    bool Started()
    {
        return started_;
    }

private:
    static void* StartThread(void* data);

    ThreadFunc func_;
    std::string thread_name_;
    pthread_t tid_;
    bool started_;
};
//--------------------------------------------------------------------
}
//--------------------------------------------------------------------
#endif // KW_THREAD_H
