//----------------------------------------------------------------------------
#ifndef KW_LOGGING_H
#define KW_LOGGING_H
//----------------------------------------------------------------------------
#include <boost/noncopyable.hpp>
#include <stdio.h>
#include "shared_lib.h"
#include "string_type.h"
#include "fmt.h"
#include "fixed_buffer.h"
#include "log_file.h"
#include "string_arg.h"
//----------------------------------------------------------------------------
namespace kw {
//----------------------------------------------------------------------------
class Log : public boost::noncopyable
{
public:
    typedef FixedBuffer<kSmallBuffer> Buffer;
    typedef void (*OutputFunc)(const char*, int);
    typedef void (*FlushFunc)();

    enum LogLevel
    {
        DEBUG,
        ERROR,
        FATAL,
        INFO,
        WARN,
        LogLevelEnd
    };

    static const char* LogLevelStr[LogLevelEnd];

public:
    Log(LogLevel log_level, const char* file, int line);
    ~Log();

    static inline void SetOutputFunc(OutputFunc output_func){ output_func_ = output_func; }
    static inline void SetFlushFunc(FlushFunc flush_func){ flush_func_ = flush_func; }

    Log& operator << (char* val)
    {
        if(unlikely(0 == val))
            buffer_.append("(null)", strlen("(null)"));
        else
            buffer_.append(val, strlen(val));

        return *this;
    }

    Log& operator << (const char* val)
    {
        if(unlikely(0 == val))
            buffer_.append("(null)", strlen("(null)"));
        else
            buffer_.append(val, strlen(val));

        return *this;
    }

    Log& operator << (const string& val)
    {
        buffer_.append(val.c_str(), val.length());

        return *this;
    }

    Log& operator << (string& val)
    {
        buffer_.append(val.c_str(), val.length());

        return *this;
    }

    template<class T>
    Log& operator << (T val)
    {
        StringType fmt_to_str(val);
        buffer_.append(fmt_to_str.Data(), fmt_to_str.Length());
        return *this;
    }

private:
    void FormatTime();
    static void DefaultOutputFunc(const char* val, int len);
    static void DefaultFlushFunc();

private:
    const char* file_;
    int line_;
    Buffer buffer_;
    LogLevel level_;

    time_t last_second_;
    char time_buf_[32];

    static OutputFunc output_func_;
    static FlushFunc flush_func_;
};
//----------------------------------------------------------------------------
}
//----------------------------------------------------------------------------
#define LOG_DEBUG   kw::Log(kw::Log::INFO, __FILE__, __LINE__)
#define LOG_EREROR  kw::Log(kw::Log::ERROR, __FILE__, __LINE__)
#define LOG_FATAL   kw::Log(kw::Log::FATAL, __FILE__, __LINE__)
#define LOG_INFO    kw::Log(kw::Log::INFO, __FILE__, __LINE__)
#define LOG_WARN    kw::Log(kw::Log::WARN, __FILE__, __LINE__)
//----------------------------------------------------------------------------
#endif // KW_LOGING_H
