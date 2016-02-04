//----------------------------------------------------------------------------
#include <gtest/gtest.h>
#include "file_reader.h"
//----------------------------------------------------------------------------
TEST(ReadSmallFileTest, Default)
{
    kw::SmallFileReader small_file_reader("/proc/self/stat");

    std::string buf;
    int err = small_file_reader.ToString(&buf, 1024);

    EXPECT_EQ(0, err);
}
//----------------------------------------------------------------------------
