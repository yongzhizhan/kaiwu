//--------------------------------------------------------------------
#ifndef KW_FILE_READER_H
#define KW_FILE_READER_H
//--------------------------------------------------------------------
#include <stdio.h>
#include <string>
#include "string_arg.h"
//--------------------------------------------------------------------
namespace kw {
//--------------------------------------------------------------------
class SmallFileReader
{
public:
    SmallFileReader(StringArg path);
    ~SmallFileReader();

    int ToString(std::string* buffer, int max_size);

private:
    static const int kBufferSize = 64 * 1024;

    FILE* fd_;
    char buf_[kBufferSize];
};
//--------------------------------------------------------------------
}
//--------------------------------------------------------------------
#endif // KW_FILE_READER_H
