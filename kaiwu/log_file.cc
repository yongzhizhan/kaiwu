//----------------------------------------------------------------------------
#include "log_file.h"
//----------------------------------------------------------------------------
namespace kw
{
//----------------------------------------------------------------------------
LogFile::LogFile(StringArg file_path, bool thread_safe, int check_second, int check_num)
    : file_appender_(file_path),
      mutex_(thread_safe == false ? 0 : new Mutex),
      thread_safe_(thread_safe),
      check_second_(check_second),
      check_num_(check_num),
      last_check_time_(0),
      count_(0)
{
}
//----------------------------------------------------------------------------
LogFile::~LogFile()
{
}
//----------------------------------------------------------------------------
int LogFile::append(StringArg buf, int size)
{
    int ret = 0;
    if(true == thread_safe_)
    {
        MutexGuard guard(*mutex_);
        ret = append_unlocked(buf, size);
    }
    else
    {
        ret = append_unlocked(buf, size);
    }

    return ret;
}
//----------------------------------------------------------------------------
int LogFile::append_unlocked(StringArg buf, int size)
{
    int ret = file_appender_.append(buf.data(), size);
    if(0 != ret)
        return ret;

    count_++;
    time_t now = time(0);
    if(count_ >= check_num_ || now - last_check_time_ > check_second_)
    {
        flush_unlocked();
        count_ = 0;
        last_check_time_ = now;
    }

    return ret;
}
//----------------------------------------------------------------------------
void LogFile::flush()
{
    if(true == thread_safe_)
    {
        MutexGuard guard(*mutex_);
        flush_unlocked();
    }
    else
    {
        flush_unlocked();
    }
}
//----------------------------------------------------------------------------
void LogFile::flush_unlocked()
{
    file_appender_.flush();
}
//----------------------------------------------------------------------------
}
//----------------------------------------------------------------------------
