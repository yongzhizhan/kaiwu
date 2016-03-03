#include <gtest/gtest.h>
#include <memory_buffer.h>

class MemoryBufferTest : public testing::Test
{
public:
    void SetUp()
    {
    }

    void TearDown()
    {
    }
};

TEST_F(MemoryBufferTest, Default)
{
    kw::MemoryBuffer buf;

    buf.Append("12345", 6);

    EXPECT_STREQ("12345", buf.Data());
}

TEST_F(MemoryBufferTest, Insert)
{
    kw::MemoryBuffer buf;
    buf.Append("123", 4);
    EXPECT_STREQ(buf.Data(), "123");
    EXPECT_EQ(buf.Length(), 4);

    buf.Insert(5, "123", 4);
    EXPECT_EQ(buf.Length(), 9);

    memcmp("123\0\0123\0", buf.Data(), 9);
}

TEST_F(MemoryBufferTest, Append)
{
    kw::MemoryBuffer buf;
    buf.Append("123");
    EXPECT_STREQ(buf.Data(), "123");
    EXPECT_EQ(buf.Length(), 4);
}
