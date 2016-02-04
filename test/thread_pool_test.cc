#include <gtest/gtest.h>
#include <tr1/memory>
#include "count_down_latch.h"
#include "thread_pool.h"

int kCountPrint = 0;

void print()
{
    printf("running...\n");
    kCountPrint++;
}

TEST(ThreadPoolTest, Default)
{
    kw::ThreadPool::ThreadTask task = std::tr1::bind(&print);

    kw::ThreadPool thread_pool(5);
    thread_pool.Start();

    int task_count = 10;
    for(int i=0; i<task_count; i++)
        thread_pool.Run(task);

    //add count down latch
    kw::CountDownLatch latch(1);
    thread_pool.Run(std::tr1::bind(&kw::CountDownLatch::CountDown, &latch));

    latch.Wait();

    thread_pool.Stop();

    EXPECT_EQ(task_count, kCountPrint);
}


