//---------------------------------------------------------------------------
#include <cstring>
#include <cstdarg>
#include <unistd.h>
#include <mutex>
#include "logger.h"
//---------------------------------------------------------------------------
namespace base
{

//---------------------------------------------------------------------------
const char* kLevelNames[]       = {"[TRACE]:", "[DEBUG]:", "[INFO]:", "[WARN]:", "[ERROR]:", "[CRITICAL]:", "[OFF]:"};
const char* kLevelShortNames[]  = {"[T]:", "[D]:", "[I]:", "[W]:", "[E]:", "[C]:", "[O]:"};

const char* LevelToString(Logger::Level lv)      { return kLevelNames[lv]; }
const char* LevelToShortString(Logger::Level lv) { return kLevelShortNames[lv]; }
//---------------------------------------------------------------------------
#define BUILD_LOG(_X_) va_list ap;                  \
    va_start(ap, format);                           \
        int err_code = vasprintf(&_X_, format, ap); \
    va_end(ap);                                     \
    if(0 > err_code)                                \
        return;                                     \
//---------------------------------------------------------------------------
class null_mutex
{
public:
    void lock(){}
    void unlock(){}
    bool try_lock(){return true;}
};
//---------------------------------------------------------------------------
class Slot 
{
public:
    Slot(){}
    virtual ~Slot(){}
    virtual void log(Logger::Level lv, const char* msg) =0;
    virtual void flush(){}
};
//---------------------------------------------------------------------------
template<class Mutex>
class BaseSlot : public Slot
{
public:
    BaseSlot(){}
    virtual ~BaseSlot(){}
    virtual void log(Logger::Level lv, const char* msg)
    {
        std::lock_guard<Mutex> lock(mutex_);

        do_log(lv, msg);
    }
    virtual void flush() =0;

protected:
    virtual void do_log(Logger::Level lv, const char* msg)=0;
    Mutex mutex_;
};
//---------------------------------------------------------------------------
template<class Mutex>
class ConsoleSlot : public BaseSlot<Mutex>
{
public:
    ConsoleSlot(){}
    virtual ~ConsoleSlot(){}
    virtual void flush(){}

protected:
    virtual void do_log(Logger::Level lv, const char* msg)
    {
        const char* level = LevelToString(lv);
        size_t size = strlen(level);
        fwrite(level, sizeof(char), size, stdout);
        fwrite(msg, sizeof(char), strlen(msg), stdout);
        fwrite("\r\n", sizeof(char), 2, stdout);
        return;
    }
};
using ConsoleSlotM = ConsoleSlot<std::mutex>;
using ConsoleSlotS = ConsoleSlot<null_mutex>;
//---------------------------------------------------------------------------
void Logger::Flush()
{
    for(const auto& v: slots_)
        v->flush();

    return;
}
//---------------------------------------------------------------------------
std::shared_ptr<Logger> Logger::stdout_logger_mt(const std::string& logger_name)
{
    SlotPtr ptr = std::make_shared<ConsoleSlotM>();
    return std::make_shared<Logger>(logger_name, ptr);
}
//---------------------------------------------------------------------------
std::shared_ptr<Logger> Logger::stdout_logger_st(const std::string& logger_name)
{
    SlotPtr ptr = std::make_shared<ConsoleSlotS>();
    return std::make_shared<Logger>(logger_name, ptr);
}
//---------------------------------------------------------------------------
void Logger::log(Level lv, const char* format, ...)
{
    if(!ShouldLog(lv))
        return;

    //build log
    char* buffer = 0;
    BUILD_LOG(buffer);

    WriteToSlots(buffer, lv);
    free(buffer);

    return;
}
//---------------------------------------------------------------------------
void Logger::trace(const char* format, ...)
{
    if(!ShouldLog(TRACE))
        return;

    //build log
    char* buffer = 0;
    BUILD_LOG(buffer);

    WriteToSlots(buffer, TRACE);
    free(buffer);

    return;
}
//---------------------------------------------------------------------------
void Logger::debug(const char* format, ...)
{
    if(!ShouldLog(DEBUG))
        return;

    //build log
    char* buffer = 0;
    BUILD_LOG(buffer);

    WriteToSlots(buffer, DEBUG);
    free(buffer);

    return;
}
//---------------------------------------------------------------------------
void Logger::info(const char* format, ...)
{
    if(!ShouldLog(INFO))
        return;

    //build log
    char* buffer = 0;
    BUILD_LOG(buffer);

    WriteToSlots(buffer, INFO);
    free(buffer);

    return;
}
//---------------------------------------------------------------------------
void Logger::warn(const char* format, ...)
{
    if(!ShouldLog(WARN))
        return;

    //build log
    char* buffer = 0;
    BUILD_LOG(buffer);

    WriteToSlots(buffer, WARN);
    free(buffer);

    return;
}
//---------------------------------------------------------------------------
void Logger::error(const char* format, ...)
{
    if(!ShouldLog(ERROR))
        return;

    //build log
    char* buffer = 0;
    BUILD_LOG(buffer);

    WriteToSlots(buffer, ERROR);
    free(buffer);

    return;
}
//---------------------------------------------------------------------------
void Logger::critical(const char* format, ...)
{
    if(!ShouldLog(CRITICAL))
        return;

    //build log
    char* buffer = 0;
    BUILD_LOG(buffer);

    WriteToSlots(buffer, CRITICAL);
    free(buffer);

    return;
}
//---------------------------------------------------------------------------
void Logger::off(const char* format, ...)
{
    if(!ShouldLog(OFF))
        return;

    //build log
    char* buffer = 0;
    BUILD_LOG(buffer);

    WriteToSlots(buffer, OFF);
    free(buffer);

    return;
}
//---------------------------------------------------------------------------
void Logger::WriteToSlots(const char* msg, Level lv)
{
    for(const auto& v : slots_)
        v->log(lv, msg);

    if(ShouldFlush(lv))
        Flush();

    return;
}

}//namespace base
//---------------------------------------------------------------------------
