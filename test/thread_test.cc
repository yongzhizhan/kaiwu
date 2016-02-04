//----------------------------------------------------------------------------
#include <tr1/functional>
#include <gtest/gtest.h>
#include "thread.h"
#include "thread_info.h"
//----------------------------------------------------------------------------
class ThreadTest : public testing::Test
{
public:
    void SetUp()
    {

    }

    void TearDown()
    {

    }

    void ThreadFunc()
    {
        EXPECT_TRUE(true);
    }
};
//--------------------------------------------------------------------
TEST_F(ThreadTest, BindFuncRun)
{
    kw::Thread::ThreadFunc func = std::tr1::bind(&ThreadTest::ThreadFunc, this);
    kw::Thread thread(func);
    thread.Start();

    thread.Join();
}
//----------------------------------------------------------------------------
TEST_F(ThreadTest, ThreadId)
{
    EXPECT_NE(kw::thread_info::ThreadId(), 0);
}
//----------------------------------------------------------------------------
TEST_F(ThreadTest, Started)
{
    kw::Thread::ThreadFunc func = std::tr1::bind(&ThreadTest::ThreadFunc, this);
    kw::Thread thread(func);
    thread.Start();

    EXPECT_TRUE(thread.Started());

    thread.Join();

    EXPECT_FALSE(thread.Started());
}
//----------------------------------------------------------------------------
