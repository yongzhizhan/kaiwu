//----------------------------------------------------------------------------
#ifndef KW_FIXEDBUFFER_H
#define KW_FIXEDBUFFER_H
//----------------------------------------------------------------------------
#include <assert.h>
//----------------------------------------------------------------------------
#define kLargeBuffer (4 * 1024 * 1024)
#define kSmallBuffer (4 * 1024)
//----------------------------------------------------------------------------
template<int Size>
class FixedBuffer
{
public:
    FixedBuffer()
        :cur_(buf_)
    {
        SetCookie(StartCookie);
    }

    ~FixedBuffer()
    {
        SetCookie(EndCookie);
    }

    void append(const char* buf, int len)
    {
        assert(sizeof buf_ - Length() >= len);
        memcpy(cur_, buf, len);
        cur_ += len;
    }

    const char* Data() const
    {
        return buf_;
    }

    int Length() const
    {
        return cur_ - buf_;
    }

    void BZero()
    {
        ::bzero(buf_, sizeof buf_);
    }

    void Reset()
    {
        cur_ = 0;
    }

    void SetCookie(void (*cookie)())
    {
        cookie_ = cookie;
    }

    static void StartCookie(){}
    static void EndCookie(){}

private:
    void (*cookie_)();
    char buf_[Size];
    char* cur_;
};
//----------------------------------------------------------------------------
#endif // KW_FIXEDBUFFER_H
