//----------------------------------------------------------------------------
#ifndef KW_PROCESSINFO_H
#define KW_PROCESSINFO_H
//----------------------------------------------------------------------------
#include <time.h>
#include <vector>
//----------------------------------------------------------------------------
namespace kw {
//----------------------------------------------------------------------------
namespace ProcessInfo
{
    extern time_t g_StartTime;
    extern int g_clockTicks;
    extern int g_pageSize;

    pid_t pid();
    string pidString();
    uid_t uid();
    string username();
    uid_t euid();
    time_t startTime();
    int clockTicksPerSecond();
    int pageSize();
    bool isDebugBuild();  // constexpr

    string hostname();
    string procname();

    /// read /proc/self/status
    string proc_status();

    /// read /proc/self/stat
    string procStat();

    /// read /proc/self/task/tid/stat
    string threadStat();

    /// readlink /proc/self/exe
    string exePath();

    int openedFiles();
    int maxOpenFiles();

    struct CpuTime
    {
    double userSeconds;
    double systemSeconds;

    CpuTime() : userSeconds(0.0), systemSeconds(0.0) { }
    };
    CpuTime cpuTime();

    int numThreads();
    std::vector<pid_t> threads();
}
//----------------------------------------------------------------------------
}
//----------------------------------------------------------------------------
#endif // KW_PROCESSINFO_H
