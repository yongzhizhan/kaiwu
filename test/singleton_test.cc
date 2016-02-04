#include <gtest/gtest.h>
#include <boost/noncopyable.hpp>
#include <singleton.h>
#include <stdio.h>

class Foo
{
public:
    Foo(){}

public:
    void PrintBar()
    {
        printf("Bar Bar\n");
    }
};

#define FooSingleton kw::Singleton<Foo>::Instance()

TEST(SingletonTest, Default)
{
    FooSingleton.PrintBar();
}

