//--------------------------------------------------------------------
#ifndef KW_FILE_BASENAME_H
#define KW_FILE_BASENAME_H
//--------------------------------------------------------------------
namespace kw {
//--------------------------------------------------------------------
class FileBasename
{
public:
    template<int N>
    FileBasename(const char (&ary)[N])
    {
        size_ = N;
        data_ = ary;

        const char* slash = strrchr(ary, '/');
        if(0 == slash)
            return;

        data_ = slash + 1;
        size_ = N - (data_ - ary);
    }

    FileBasename(const char *path)
    {
        const char* slash = strrchr(path, '/');
        if(0 == slash)
            data_ = (char*)path;
        else
            data_ = slash + 1;

        size_ = strlen(data_);
    }

    const char* data() { return data_; }
    int size() { return size_; }

private:
    const char* data_;
    int size_;
};
//--------------------------------------------------------------------
}
#endif // KW_FILE_BASENAME_H
