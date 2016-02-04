//----------------------------------------------------------------------------
#include <gtest/gtest.h>
#include <time.h>
#include <auto_ptr.h>
#include "log_file.h"
#include "log.h"
//----------------------------------------------------------------------------
class LogTest : public testing::Test
{
protected:
    void SetUp()
    {
        const char* path = "/tmp/LogTest_ToFile.log";
        unlink(path);

        logFile.reset(new kw::LogFile(path));
    }

    void TearDown()
    {
        logFile.release();
    }

    static void MyLogAppend(const char* val, int len)
    {
        LogTest::logFile->append(val, len);
    }

    static void MyLogFlush()
    {
        LogTest::logFile->flush();
    }

public:
    static std::auto_ptr<kw::LogFile> logFile;
};
//----------------------------------------------------------------------------
std::auto_ptr<kw::LogFile> LogTest::logFile;
//----------------------------------------------------------------------------
TEST_F(LogTest, HandleStreamOutput)
{
    string test = "1234";
    LOG_INFO << test;
}
//----------------------------------------------------------------------------
TEST_F(LogTest, Serialize)
{
    LOG_INFO << "1" << "2" << "3";
}
//----------------------------------------------------------------------------
TEST_F(LogTest, ToFile)
{
    kw::Log::SetOutputFunc(&LogTest::MyLogAppend);
    kw::Log::SetFlushFunc(&LogTest::MyLogFlush);

    LOG_INFO << "1" << "1" << "1";
    LOG_INFO << "2" << "2" << "2";
}
//----------------------------------------------------------------------------
TEST_F(LogTest, Count100W)
{
    kw::Log::SetOutputFunc(&LogTest::MyLogAppend);
    kw::Log::SetFlushFunc(&LogTest::MyLogFlush);

    char buf[100] = "abcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcd";
    size_t start = time(0);
    for(int i=0; i<100 * 10000; i++)
    {
        LOG_INFO << buf;
    }

    size_t erase_time = time(0) - start;
    EXPECT_LE(erase_time, 5);
}
//----------------------------------------------------------------------------
