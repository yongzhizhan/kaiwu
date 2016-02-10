//--------------------------------------------------------------------
#include <assert.h>
#include <errno.h>
#include <algorithm>
#include "file_reader.h"
//--------------------------------------------------------------------
namespace kw {
//--------------------------------------------------------------------
SmallFileReader::SmallFileReader(StringArg path)
    :fd_(fopen(path.data(), "re"))
{
    assert(0 != fd_);

    setbuffer(fd_, buf_, sizeof buf_);
}
//--------------------------------------------------------------------
SmallFileReader::~SmallFileReader()
{
    if(0 != fd_)
        fclose(fd_);
}
//--------------------------------------------------------------------
int SmallFileReader::ToString(std::string* buffer, int size)
{
    assert(0 != buffer);

    buffer->clear();

    int size_readed = std::min(size, static_cast<int>(sizeof buf_));
    size_t count = fread(buf_, 1, size_readed, fd_);
    if(0 >= count)
        return 0;

    buffer->reserve(size);
    buffer->insert(buffer->end(), buf_, buf_ + count);

    do
    {
        size -= count;
        size_readed = std::min(size, (int)sizeof buf_);
        count = fread(buf_, 1, size_readed, fd_);
        if(0 == count)
            break;

        if(0 < count)
            return errno;

        buffer->insert(buffer->end(), buf_, buf_ + count);
    }while(true);

    return 0;
}
//--------------------------------------------------------------------
}
