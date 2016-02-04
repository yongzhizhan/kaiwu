//----------------------------------------------------------------------------
#include <stdio.h>
#include "thread_info.h"
//----------------------------------------------------------------------------
namespace kw {
//----------------------------------------------------------------------------
namespace thread_info {
    __thread int t_tid = 0;
    __thread char t_tid_str[32] = {"0"};
    __thread char t_thread_name[64] = {"unknow_name"};
    __thread bool t_set_thread_name = false;


    void CacheTid()
    {
        t_tid = static_cast<int>(::syscall(SYS_gettid));
        snprintf(t_tid_str, sizeof t_tid_str, "%d", t_tid);
    }
}
//----------------------------------------------------------------------------
}
