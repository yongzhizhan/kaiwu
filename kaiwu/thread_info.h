//----------------------------------------------------------------------------
#ifndef KW_CURRENTTHREAD_H
#define KW_CURRENTTHREAD_H
//----------------------------------------------------------------------------
#include <unistd.h>
#include <sys/syscall.h>
#include "shared_lib.h"
//----------------------------------------------------------------------------
namespace kw {
//----------------------------------------------------------------------------
namespace thread_info
{
    extern __thread int t_tid;
    extern __thread char t_tid_str[32];
    extern __thread char t_thread_name[64];
    extern __thread bool t_set_thread_name;

    void CacheTid();

    inline int ThreadId()
    {
        if(unlikely(t_tid == 0))
            CacheTid();

        return t_tid;
    }

    inline const char* ThreadName()
    {
        if(true == t_set_thread_name)
            return t_thread_name;

        if(::getpid() == ThreadId())
            return "main_thread";

        snprintf(t_thread_name, sizeof t_thread_name, "thread_%d", ThreadId());
        return t_thread_name;
    }

    inline char* ThreadIdStr()
    {
        return t_tid_str;
    }
}
//----------------------------------------------------------------------------
}
//----------------------------------------------------------------------------
#endif // KW_CURRENTTHREAD_H
