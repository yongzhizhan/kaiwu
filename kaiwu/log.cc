//----------------------------------------------------------------------------
#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <assert.h>
#include "shared_lib.h"
#include "thread_info.h"
#include "log.h"
#include "file_basename.h"
//----------------------------------------------------------------------------
namespace kw
{
//----------------------------------------------------------------------------
Log::OutputFunc Log::output_func_ = Log::DefaultOutputFunc;
Log::FlushFunc Log::flush_func_ = Log::DefaultFlushFunc;
//----------------------------------------------------------------------------
const char* Log::LogLevelStr[LogLevelEnd] = { "DEBUG", "ERROR", "FATAL", "INFO", "WARN"};
//----------------------------------------------------------------------------
Log::Log(LogLevel Log_level, const char* file, int line)
    :file_(file), line_(line), level_(Log_level), last_second_(0)
{
    assert(Log_level < sizeof LogLevelStr);

    FormatTime();
    *this << kw::thread_info::ThreadId() << " " << LogLevelStr[Log_level] << " ";
}
//----------------------------------------------------------------------------
Log::~Log()
{
    *this << " " << FileBasename(file_).data() << ":" << line_ << "\n";
    output_func_(buffer_.Data(), buffer_.Length());
    flush_func_();

    if(FATAL == level_)
        abort();
}
//----------------------------------------------------------------------------
void Log::FormatTime()
{
    struct timeval tv;
    if(-1 == gettimeofday(&tv, 0))
    {
        *this << "1970-01-01 00:00:00" << " ";
        return;
    }

    if(last_second_ != tv.tv_sec)
    {
        struct tm tm_time;
        gmtime_r(&tv.tv_sec, &tm_time);

        strftime(time_buf_, sizeof(time_buf_), "%Y-%m-%d %H-%M-%S", &tm_time);
        last_second_ = tv.tv_sec;
    }

    *this << time_buf_ << " ";
}
//----------------------------------------------------------------------------
void Log::DefaultOutputFunc(const char* val, int len)
{
    write(1, val, len);
}
//----------------------------------------------------------------------------
void Log::DefaultFlushFunc()
{
}
//----------------------------------------------------------------------------
}
//----------------------------------------------------------------------------
