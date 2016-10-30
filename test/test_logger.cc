//---------------------------------------------------------------------------
#include <unistd.h>
#include "../src/logger.h"
#include "test_logger.h"
#include "../src/log_file.h"
//---------------------------------------------------------------------------
using namespace base;
using namespace base::test;
//---------------------------------------------------------------------------
const char* kLogDebug   = "hello, debug";
const char* kLogInfo    = "hello, info";
const char* kLogWarning = "hello, warning";
const char* kLogError   = "hello, error";
//---------------------------------------------------------------------------
bool TestLogger::DoTest()
{
    //if(false == Test_Illegal())     return false;
    if(false == Test_Console())     return false;
    //if(false == Test_Date())        return false;

    return true;
}
//---------------------------------------------------------------------------
bool TestLogger::Test_Illegal()
{
    //初始化失败
    {
    LogFile log_file;
    MY_ASSERT(false == log_file.Initialze("", "", "", 0));
    MY_ASSERT(false == log_file.Initialze("my title", "", "", 0));
    MY_ASSERT(false == log_file.Initialze("my title", "/tmp", "", 0));

    MY_ASSERT(false == log_file.WriteLog(LogFile::LOGLEVEL_DEBUG, "my first log"));
    }

    {
    const char* path = "/tmp/test_log";
    const char* name = "mylog";
    LogFile log_file;
    MY_ASSERT(true == log_file.Initialze("my title", path, name, 1024*1024));
    for(int i=0; i<10; i++)
    {
        MY_ASSERT(true == log_file.WriteLog(LogFile::LOGLEVEL_DEBUG,      kLogDebug));
        MY_ASSERT(true == log_file.WriteLog(LogFile::LOGLEVEL_INFO,       kLogInfo));
        MY_ASSERT(true == log_file.WriteLog(LogFile::LOGLEVEL_WARNING,    kLogDebug));
        MY_ASSERT(true == log_file.WriteLog(LogFile::LOGLEVEL_ERROR,      kLogDebug));
    }
    }

    return true;
}
//---------------------------------------------------------------------------
bool TestLogger::Test_Console()
{
    const char* logger_name = "haha";
    auto logger = Logger::stdout_logger_mt(logger_name);
    std::cout << "name:" << logger->name() << std::endl;
    MY_ASSERT(logger->name() == logger_name);

    logger->set_level(Logger::TRACE);
    std::cout << "level:" << logger->level() << std::endl;
    MY_ASSERT(logger->level() == Logger::TRACE);

    logger->set_flush_level(Logger::ERROR);
    std::cout << "flush level:" << logger->flush_level() << std::endl;
    MY_ASSERT(logger->flush_level() == Logger::ERROR);

    const char* msg = "you are sb";
    logger->trace(msg);
    //logger->trace("%s", msg);
   // logger->trace(msg);
   // logger->trace(msg);
   // logger->trace(msg);
   // logger->trace(msg);
   // logger->trace(msg);
   // logger->trace(msg);

    return true;
}
//---------------------------------------------------------------------------
bool TestLogger::Test_Date()
{
    const char* path = "/tmp/test_log";
    const char* name = "mylog_date";
    LogFile log_file;

    MY_ASSERT(true == log_file.Initialze("date test", path, name, 1024*1024));
    for(size_t i=0; i<50; i++)
    {
        MY_ASSERT(true == log_file.WriteLog(LogFile::LOGLEVEL_DEBUG,      kLogDebug));
        sleep(1);
    }

    log_file.WriteLog(LogFile::LOGLEVEL_INFO, "==.............end date");
    return true;
}
//---------------------------------------------------------------------------
