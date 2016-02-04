//----------------------------------------------------------------------------
#include <gtest/gtest.h>
#include "fmt.h"
#include "thread.h"
#include "thread_info.h"
#include "mutex.h"
//----------------------------------------------------------------------------
class MutexTest : public testing::Test
{
public:
    void SetUp()
    {
        run_count = 0;
    }

    void TearDown()
    {
    }

    void ThreadFunc_Default()
    {
        kw::MutexGuard mutex_guard(mutex);

        for(int i=0; i<20; i++)
        {
            printf("Thread:%s, Index:%d\n", kw::thread_info::ThreadName(), i);
            fsync(1);
        }

        run_count++;
    }

protected:
    kw::Mutex mutex;
    int run_count;
};
//----------------------------------------------------------------------------
TEST_F(MutexTest, Default)
{
    for(int i=0; i<10; i++)
    {
        kw::Thread::ThreadFunc func = std::tr1::bind(&MutexTest::ThreadFunc_Default, this);

        kw::Thread thread(func);
        thread.Start();
    }

    while(10 > run_count)
        sleep(2);

    sleep(2);
}
//----------------------------------------------------------------------------
