//---------------------------------------------------------------------------
#include "logger.h"
//---------------------------------------------------------------------------
namespace base
{

namespace
{

#define BUILD_LOG va_list ap;\
    va_start(ap, format);\
        char* buffer = 0;\
        int err_code = vasprintf(&buffer, format, ap);\
    va_end(ap);\
    if(0 > err_code)\
        return;

}
//---------------------------------------------------------------------------
class Slot 
{
public:
    virtual void log(Logger::Level lv, const std::string& msg) =0;
    virtual void flush() =0;
};
//---------------------------------------------------------------------------
const char* Logger::kLevelNames[] = {"TRACE", "DEBUG", "INFO", "WARN", "ERROR", "CRITICAL", "OFF"};
const char* Logger::kLevelShortNames[] = {"T", "D", "I", "W", "E", "C", "O"};
//---------------------------------------------------------------------------
void Logger::Flush()
{
    for(const auto& v: slots_)
        v->flush();

    return;
}
//---------------------------------------------------------------------------
void Logger::log(Level lv, const char* log)
{
    if(!ShouldLog(lv))
        return;

    WriteToSlots(log, lv);
    return;
}
//---------------------------------------------------------------------------
void Logger::log(Level lv, const char* format, ...)
{
    if(!ShouldLog(lv))
        return;

    /*//build log
    va_list ap;
    va_start(ap, format);
        char* buffer = 0;
        int err_code = vasprintf(&buffer, format, ap);
    va_end(ap);
    if(0 > err_code)
        return;

    WriteToSlots(buffer, lv);
    free(buffer);
    */
    BUILD_LOG;
    WriteToSlots(buffer, lv);
    free(buffer);
    return;
}
//---------------------------------------------------------------------------
void Logger::trace(Level lv, const char* format, ...)
{
    va_list ap;
    va_start(ap, format);
        char* buffer = catvsprint(format, ap);
    va_end(ap);

    if(0 == buffer)
        return;

    WriteToSlots(buffer, lv);
    free(buffer);
    return;
}
//---------------------------------------------------------------------------
void Logger::debug(Level lv, const char* format, ...)
{
    if(!ShouldLog(DEBUG))
        return;

    return;
}
//---------------------------------------------------------------------------
void Logger::info(Level lv, const char* format, ...)
{
    if(!ShouldLog(INFO))
        return;

    return;
}
//---------------------------------------------------------------------------
void Logger::warn(Level lv, const char* format, ...)
{
    if(!ShouldLog(WARN))
        return;

    return;
}
//---------------------------------------------------------------------------
void Logger::error(Level lv, const char* format, ...)
{
    if(!ShouldLog(ERROR))
        return;

    return;
}
//---------------------------------------------------------------------------
void Logger::critical(Level lv, const char* format, ...)
{
    if(!ShouldLog(CRITICAL))
        return;

    return;
}
//---------------------------------------------------------------------------
void Logger::off(Level lv, const char* format, ...)
{
    if(!ShouldLog(OFF))
        return;

    return;
}
//---------------------------------------------------------------------------
void Logger::WriteToSlots(const std::string& log, Level lv)
{
    for(const auto& v : slots_)
        v->log(lv, log);

    if(ShouldFlush(lv))
        Flush();

    return;
}
//---------------------------------------------------------------------------

}//namespace base
//---------------------------------------------------------------------------



