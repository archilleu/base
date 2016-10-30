//---------------------------------------------------------------------------
#ifndef BASE_LOGGER_H_
#define BASE_LOGGER_H_
//---------------------------------------------------------------------------
#include <string>
#include <vector>
#include <memory>
//---------------------------------------------------------------------------
namespace base
{

//---------------------------------------------------------------------------
using SlotPtr = std::shared_ptr<class Slot>;
//---------------------------------------------------------------------------
class Logger 
{
public:
    enum Level
    {
        TRACE =0,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        CRITICAL,
        OFF
    };

    Logger(const std::string& logger_name, std::vector<SlotPtr> slots)
    :   name_(logger_name),
        level_(INFO),
        flush_level_(OFF),
        slots_(slots)
    {
    }
    Logger(const std::string& logger_name, SlotPtr slot)
    :   Logger(logger_name, std::vector<SlotPtr>(1, slot))
    {
    }
    virtual ~Logger(){}
    Logger(Logger&) =delete;
    Logger& operator=(Logger&) =delete;

    void set_level(Level lv) { level_ = lv; }
    Level level() const { return level_; }

    void set_flush_level(Level lv) { flush_level_ = lv; }
    Level flush_level() const { return flush_level_; }

    const std::string& name() const { return name_; }

    void Flush();


    //log
    void log        (Level lv, const char* format, ...);
    void trace      (const char* format, ...);
    void debug      (const char* format, ...);
    void info       (const char* format, ...);
    void warn       (const char* format, ...);
    void error      (const char* format, ...);
    void critical   (const char* format, ...);
    void off        (const char* format, ...);

public:
    //Create logger
    static std::shared_ptr<Logger> stdout_logger_mt(const std::string& logger_name);
    static std::shared_ptr<Logger> stdout_logger_st(const std::string& logger_name);

private:
    bool ShouldLog(Level lv) const { return level_ >= lv; }
    bool ShouldFlush(Level lv) const { return flush_level_ >= lv; }

    void WriteToSlots(const char* msg, Level lv);

private:
    std::string name_;
    Level level_;
    Level flush_level_;
    std::vector<SlotPtr> slots_;
};

}//namespace base
//---------------------------------------------------------------------------
#endif //BASE_LOGGER_H_
