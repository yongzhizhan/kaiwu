#include <gtest/gtest.h>
#include <tr1/memory>
#include <signal_slot.h>
#include <thread.h>

static int kCount;

void SlotFunctor(int)
{
    kCount++;
    printf("kCount:%d\n", kCount);
}

class SignalSlotTest : public testing::Test
{
public:
    void SetUp()
    {
        kCount = 0;
    }

    void TearDown()
    {

    }   

    void ThreadFun()
    {
        printf("Run ThreadFun\n");
        for(int i=0; i<100; i++)
        {
            kw::Signal<void(int)> signal;
            kw::SlotHandle slot = signal.Connect(std::tr1::bind(SlotFunctor, std::tr1::placeholders::_1));
            signal.Emit(1);
        }
    }
};

TEST_F(SignalSlotTest, Default)
{
    kw::Signal<void(int)> signal;
    kw::SlotHandle slot = signal.Connect(std::tr1::bind(SlotFunctor, std::tr1::placeholders::_1));
    signal.Emit(1);

    EXPECT_EQ(1, kCount);
}

TEST_F(SignalSlotTest, Disconnect)
{
    kw::Signal<void(int)> signal;

    {
        kw::SlotHandle slot = signal.Connect(std::tr1::bind(SlotFunctor, std::tr1::placeholders::_1));
    }

    signal.Emit(1);

    EXPECT_EQ(0, kCount);
}

TEST_F(SignalSlotTest, ThreadRun)
{
    kw::Thread thread1(std::tr1::bind(&SignalSlotTest::ThreadFun, this));
    kw::Thread thread2(std::tr1::bind(&SignalSlotTest::ThreadFun, this));
    kw::Thread thread3(std::tr1::bind(&SignalSlotTest::ThreadFun, this));
    kw::Thread thread4(std::tr1::bind(&SignalSlotTest::ThreadFun, this));

    thread1.Start();
    thread2.Start();
    thread3.Start();
    thread4.Start();

    thread1.Join();
    thread2.Join();
    thread3.Join();
    thread4.Join();
}

TEST_F(SignalSlotTest, Queue)
{
    //
}

