//----------------------------------------------------------------------------
#ifndef KW_FILE_APPENDER_H
#define KW_FILE_APPENDER_H
//----------------------------------------------------------------------------
#include <boost/noncopyable.hpp>
#include <stdio.h>
#include "string_arg.h"
//----------------------------------------------------------------------------
namespace kw {
//----------------------------------------------------------------------------
class FileAppender : public boost::noncopyable
{
public:
    FileAppender(StringArg file_path);
    ~FileAppender();

    int append(const char* buf, int size);
    void flush();

private:
    FILE* fd_;
};
//----------------------------------------------------------------------------
}
//----------------------------------------------------------------------------
#endif // KW_FILE_APPENDER_H
