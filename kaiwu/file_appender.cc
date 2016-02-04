//----------------------------------------------------------------------------
#include <errno.h>
#include <assert.h>
#include "file_appender.h"
//----------------------------------------------------------------------------
namespace kw {
//----------------------------------------------------------------------------
FileAppender::FileAppender(StringArg file_path)
    :fd_(fopen(file_path.data(), "ae"))
{
    assert(0 != fopen);
}
//----------------------------------------------------------------------------
FileAppender::~FileAppender()
{
    if(0 != fd_)
        fclose(fd_);
}
//----------------------------------------------------------------------------
int FileAppender::append(const char* buf, int size)
{
    int write_count = 0;
    int remain_size = size;

    while(0 < remain_size)
    {
        write_count = fwrite(buf + (size - remain_size), 1, remain_size, fd_);
        if(0 == write_count)
            return ferror(fd_);

        remain_size = remain_size - write_count;
    }

    return 0;
}
//----------------------------------------------------------------------------
void FileAppender::flush()
{
    fflush(fd_);
}
//----------------------------------------------------------------------------
}
//----------------------------------------------------------------------------
