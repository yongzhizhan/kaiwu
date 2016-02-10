#include <gtest/gtest.h>
#include <condition.h>
#include <thread.h>

class ConditionTest : public testing::Test
{
public:
    void SetUp()
    {
        wait_complete_ = false;
    }

    void TearDown()
    {
    }

    void ThreadFuncDefault()
    {
        kw::MutexGuard guard(mutex_);
        cond_.Wait(&mutex_);

        wait_complete_ = true;
    }

protected:
    kw::Condition cond_;
    kw::Mutex mutex_;
    bool wait_complete_;
};

TEST_F(ConditionTest, Default)
{
    kw::Thread thread(std::tr1::bind(&ConditionTest::ThreadFuncDefault, this));
    thread.Start();

    EXPECT_FALSE(wait_complete_);

    sleep(2);

    {
        kw::MutexGuard guard(mutex_);
        cond_.NotifyAll();
    }

    thread.Join();

    EXPECT_TRUE(wait_complete_);
}
