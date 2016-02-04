//----------------------------------------------------------------------------
#ifndef KW_LOG_FILE_H
#define KW_LOG_FILE_H
//----------------------------------------------------------------------------
#include <boost/noncopyable.hpp>
#include <time.h>
#include <tr1/memory>
#include "mutex.h"
#include "string_arg.h"
#include "file_appender.h"
//----------------------------------------------------------------------------
namespace kw {
//----------------------------------------------------------------------------
class LogFile : public boost::noncopyable
{
public:
    LogFile(StringArg file_path, bool thread_safe=true, int check_second=3, int check_num=1024);
    ~LogFile();

    int append(StringArg buf, int size);
    void flush();

private:
    int append_unlocked(StringArg buf, int size);
    void flush_unlocked();

private:
    FileAppender file_appender_;
    std::tr1::shared_ptr<Mutex> mutex_;
    bool thread_safe_;
    int check_second_;
    int check_num_;
    time_t last_check_time_;
    int count_;
};
//----------------------------------------------------------------------------
}
//----------------------------------------------------------------------------
#endif // KW_LOG_FILE_H
