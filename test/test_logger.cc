//---------------------------------------------------------------------------
#include "test_inc.h"
#include "../src/logger.h"
#include "../src/function.h"
#include "../src/timestamp.h"
//---------------------------------------------------------------------------
using namespace base;
using namespace base::test;
//---------------------------------------------------------------------------
static const char* path = "/tmp/logger";
static const char* illgal_path = "/proc/illegal";
//---------------------------------------------------------------------------
bool Test_Illegal()
{
    //初始化失败
    {
    auto logger = Logger::file_logger_st(illgal_path, false);

    logger->set_level(Logger::TRACE);
    std::cout << "level:" << logger->level() << std::endl;
    TEST_ASSERT(logger->level() == Logger::TRACE);

    logger->set_flush_level(Logger::ERROR);
    std::cout << "flush level:" << logger->flush_level() << std::endl;
    TEST_ASSERT(logger->flush_level() == Logger::ERROR);

    try
    {
        logger->trace("haha");
        TEST_ASSERT(false);
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    logger = Logger::file_logger_st(illgal_path, false);
    try
    {
        logger->trace("haha");
        TEST_ASSERT(false);
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    }

    return true;
}
//---------------------------------------------------------------------------
bool Test_Console()
{
    auto logger = Logger::stdout_logger_mt();

    logger->set_level(Logger::TRACE);
    std::cout << "level:" << logger->level() << std::endl;
    TEST_ASSERT(logger->level() == Logger::TRACE);

    logger->set_flush_level(Logger::ERROR);
    std::cout << "flush level:" << logger->flush_level() << std::endl;
    TEST_ASSERT(logger->flush_level() == Logger::ERROR);

    const char* msg = "you are sb";
    logger->trace(msg);
    logger->debug(msg);
    logger->info(msg);
    logger->warn(msg);
    logger->error(msg);
    logger->critical(msg);
    logger->off(msg);

    logger->trace("haha:%s", msg);
    logger->debug("haha:%s", msg);
    logger->info("haha:%s", msg);
    logger->warn("haha:%s", msg);
    logger->error("haha:%s", msg);
    logger->critical("haha:%s", msg);
    logger->off("haha:%s", msg);

    return true;
}
//---------------------------------------------------------------------------
bool Test_File()
{
    FolderDelete(path);
    auto logger = Logger::file_logger_st(path, false);

    const char* msg = "you are sb";
    //int size = 1024*1024;
    int size = 1024;
    for(int i=0; i< size; i++)
    {
        logger->trace(msg);
        logger->debug(msg);
        logger->info(msg);
        logger->warn(msg);
        logger->error(msg);
        logger->critical(msg);
        logger->off(msg);
    }
    
    for(int i=0; i< size; i++)
    {
        logger->trace("haha:%s", msg);
        logger->debug("haha:%s", msg);
        logger->info("haha:%s", msg);
        logger->warn("haha:%s", msg);
        logger->error("haha:%s", msg);
        logger->critical("haha:%s", msg);
        logger->off("haha:%s", msg);
    }

    logger->Flush();
    return true;
}
//---------------------------------------------------------------------------
bool Test_FileAndConsole()
{
    FolderDelete(path);
    auto logger = Logger::file_stdout_logger_st(path, true);

    const char* msg = "you are sb";
    //int size = 1024*1024;
    int size = 1024;
    for(int i=0; i< size; i++)
    {
        logger->trace(msg);
        logger->debug(msg);
        logger->info(msg);
        logger->warn(msg);
        logger->error(msg);
        logger->critical(msg);
        logger->off(msg);
    }
    
    for(int i=0; i< size; i++)
    {
        logger->trace("haha:%s", msg);
        logger->debug("haha:%s", msg);
        logger->info("haha:%s", msg);
        logger->warn("haha:%s", msg);
        logger->error("haha:%s", msg);
        logger->critical("haha:%s", msg);
        logger->off("haha:%s", msg);
    }

    logger->Flush();
    return true;
}
//---------------------------------------------------------------------------
int main(int, char**)
{
    TestTitle();

    Test_Illegal();
    Test_Console();
    Test_File();
    Test_FileAndConsole();

    FolderDelete(path);
    return 0;
}
//---------------------------------------------------------------------------
