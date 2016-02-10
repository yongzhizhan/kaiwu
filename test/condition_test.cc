//----------------------------------------------------------------------------
#include <gtest/gtest.h>
#include <thread.h>
#include <mutex.h>
#include <condition.h>
#include <boost/timer.hpp>

class ConditionTest : public testing::Test
{
protected:
    void SetUp()
    {
    }

    void TearDown()
    {
    }

    void start()
    {

        //cond_.Wait();
    }

    static void RunningThread()
    {
        //cond_.Notify();
    }

private:
    kw::Condition cond_;
    //kw::Thread thread;
};

//
TEST_F(ConditionTest, Default)
{
    boost::timer timer;
    cond_.Wait();


}
//----------------------------------------------------------------------------
