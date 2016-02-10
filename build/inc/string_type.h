//--------------------------------------------------------------------
#ifndef KW_FMT_TO_STR_H
#define KW_FMT_TO_STR_H
//--------------------------------------------------------------------
namespace kw {
//--------------------------------------------------------------------
class StringType
{
public:
    //integer
    StringType(bool val)                  {Format("%d", val);}
    StringType(int val)                   {Format("%d", val);}
    StringType(unsigned int val)          {Format("%d", val);}
    StringType(short val)                 {Format("%d", val);}
    StringType(unsigned short val)        {Format("%d", val);}
    StringType(long val)                  {Format("%d", val);}
    StringType(unsigned long val)         {Format("%d", val);}

    //float
    StringType(float val)                 {Format("%.12g", val);}
    StringType(double val)                {Format("%.12g", val);}

    //char
    StringType(char val)                  {Format("%c", val);}

    inline char* Data(void)               {return buf_;}
    inline int   Length(void)             {return size_;}

private:
    template<class T>
    void Format(const char* fmt, T& val)
    {
        size_ = snprintf(buf_, sizeof buf_, fmt, val);
        assert(static_cast<size_t>(size_) < sizeof buf_);
    }

private:
    char buf_[32];
    int size_;
};
//--------------------------------------------------------------------
}
//--------------------------------------------------------------------
#endif // KW_FMT_TO_STR_H
