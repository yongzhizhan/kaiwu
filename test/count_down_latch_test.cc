#include <gtest/gtest.h>
#include <count_down_latch.h>

TEST(CountDownLatchTest, Default)
{
    kw::CountDownLatch latch(1);

    EXPECT_EQ(latch.GetCount(), 1);

    latch.CountDown();

    EXPECT_EQ(latch.GetCount(), 0);
}

