//----------------------------------------------------------------------------
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include "shared_lib.h"
#include "process_info.h"
#include "thread_info.h"
#include "file_reader.h"
//----------------------------------------------------------------------------
namespace kw {
//----------------------------------------------------------------------------
namespace ProcessInfo {
    time_t g_StartTime = time(0);
    int g_clockTicks = static_cast<int>(::sysconf(_SC_CLK_TCK));
    int g_pageSize = static_cast<int>(::sysconf(_SC_PAGE_SIZE));

    pid_t pid()
    {
        return ::getpid();
    }

    string pidString()
    {
        return Fmt("%d", pid()).data();
    }

    uid_t uid()
    {
        return ::getuid();
    }

    string username()
    {
        struct passwd pwd;
        struct passwd* result = NULL;
        char buf[8192];
        const char* name = "unknownuser";

        getpwuid_r(uid(), &pwd, buf, sizeof buf, &result);
        if(result)
        {
            name = pwd.pw_name;
        }

        return name;
    }

    uid_t euid()
    {
        return ::geteuid();
    }

    time_t startTime()
    {
        return g_StartTime;
    }

    int clockTicksPerSecond()
    {
        return g_clockTicks;
    }

    int pageSize()
    {
        return g_pageSize;
    }

    bool isDebugBuild()
    {
        #ifdef NDEBUG
        return false;
        #else
        return true;
        #endif
    }

    string hostname()
    {
        char buf[128];
        if(0 == gethostname(buf, sizeof buf))
            return buf;

        return "unknownhost";
    }

    string procname()
    {
        return "";
    }

    /// read /proc/self/status
    string procStatus()
    {

    }

    /// read /proc/self/stat
    string procStat()
    {
        kw::SmallFileReader small_file_reader("/proc/self/stat");

        std::string buf;
        int err = small_file_reader.ToString(&buf, 65535);
        if(0 != err)
            buf = "error stat";

        return buf;
    }

    /// read /proc/self/task/tid/stat
    string threadStat()
    {
        return Fmt("/proc/self/task/%d/stat", thread_info::ThreadIdStr()).data();
    }

    /// readlink /proc/self/exe
    string exePath()
    {
        string result;
        char buf[1024];
        ssize_t err = ::readlink("/proc/self/exe", buf, sizeof buf);
        if (0 < err)
            result.assign(buf, err);

        return result;
    }

    int openedFiles()
    {
        return 0;
    }

    int maxOpenFiles()
    {
        return 0;
    }

    CpuTime cpuTime()
    {
        return CpuTime();
    }

    int numThreads()
    {
        return 0;
    }

    std::vector<pid_t> threads()
    {
        return std::vector<pid_t>();
    }
}
//----------------------------------------------------------------------------
}
