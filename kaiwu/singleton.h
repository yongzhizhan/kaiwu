#ifndef KW_SINGLETON_H
#define KW_SINGLETON_H

#include <stdlib.h>
#include <pthread.h>

namespace kw
{

template<class T>
class Singleton
{
public:
    static T& Instance()
    {
        pthread_once(&once_, &Init);
        return *instance_;
    }

protected:
    //disable constructor
    Singleton(){}
    ~Singleton(){}

    static void Init()
    {
        atexit(UnInit);
        instance_ = new T();
    }

    static void UnInit()
    {
        delete instance_;
    }

private:
    static T* instance_;
    static pthread_once_t once_;
};

template<class T> T* Singleton<T>::instance_ = 0;
template<class T> pthread_once_t Singleton<T>::once_ = 0;

}

#endif // KW_SINGLETON_H
