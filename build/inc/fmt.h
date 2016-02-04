//--------------------------------------------------------------------
#ifndef KW_FMT_H
#define KW_FMT_H
//--------------------------------------------------------------------
#include <stdio.h>
#include <assert.h>
//--------------------------------------------------------------------
namespace kw {
//--------------------------------------------------------------------
class Fmt
{
public:
    template<class T>
    Fmt(const char* fmt, T val)
    {
        size_ = snprintf(buf_, sizeof buf_, fmt, val);
        assert(static_cast<size_t>(size_) < sizeof buf_);
    }

    char* data() { return buf_; }
    int size() { return size_; }

private:
    char buf_[32];
    int size_;
};
//--------------------------------------------------------------------
}
//--------------------------------------------------------------------
#endif // KW_FMT_H
