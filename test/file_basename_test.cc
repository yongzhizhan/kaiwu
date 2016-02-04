//----------------------------------------------------------------------------
#include <gtest/gtest.h>
#include "file_basename.h"
//----------------------------------------------------------------------------
TEST(BasenameTest, Default)
{
    kw::FileBasename basename("path/file");
    EXPECT_STREQ(basename.data(), "file");

    char basename_str[] = "path/file";
    kw::FileBasename basename_ary(basename_str);
    EXPECT_STREQ(basename_ary.data(), "file");
}
//----------------------------------------------------------------------------
