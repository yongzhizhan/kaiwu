#ifndef KW_RESPONSE_BUFFER_H
#define KW_RESPONSE_BUFFER_H

#include <vector>

namespace kw{

class MemoryBuffer
{
public:
    void Reserve(int size)
    {
        buf_.reserve(size);
    }

    template<int N>
    MemoryBuffer& Append(const char (&ary)[N])
    {
        return Append(ary, N);
    }

    MemoryBuffer& Append(const char* buf, int len)
    {
        buf_.resize(buf_.size() + len);
        memcpy(buf_.data() + buf_.size() - len, buf, len);
        return *this;
    }

    void CopyFrom(char* buf, int len)
    {
        buf_.clear();
        buf_.resize(len, 0);
        memcpy(buf_.data(), buf, len);
    }

    void Insert(int index, char* buf, int len)
    {
        if(index == buf_.size())
        {
            Append(buf, len);
        }
        else if(index > buf_.size())
        {
            buf_.resize(index, 0);
            Append(buf, len);
        }
        else
        {
            buf_.resize(index + len, 0);
            memcpy(buf_.data() + index, buf, len);
        }
    }

    void Clear()
    {
        buf_.clear();
    }

    const char* Data() const
    {
        return buf_.data();
    }

    int Length()
    {
        return buf_.size();
    }

private:
    std::vector<char> buf_;
};

}
#endif // KW_RESPONSE_BUFFER_H
