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

using SlotPtr = std::shared_ptr<class Slot>;

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
    virtual ~Logger();
    Logger(Logger&) =delete;
    Logger& operator=(Logger&) =delete;

    void set_level(Level lv) { level_ = lv; }
    Level level() const { return level_; }

    void flush_level(Level lv) { flush_level_ = lv; }
    Level flush_level() const { return flush_level_; }

    const std::string& name() const { return name_; }

    void Flush();

    const char* LevToString(Level lv) const { return kLevelNames[lv]; }
    const char* LevToShortString(Level lv) const { return kLevelShortNames[lv]; }

    //log
    void log(Level lv, const char* log);
    void log(Level lv, const char* format, ...);
    void trace(Level lv, const char* format, ...);
    void debug(Level lv, const char* format, ...);
    void info(Level lv, const char* format, ...);
    void warn(Level lv, const char* format, ...);
    void error(Level lv, const char* format, ...);
    void critical(Level lv, const char* format, ...);
    void off(Level lv, const char* format, ...);

private:
    bool ShouldLog(Level lv) const { return level_ >= lv; }
    bool ShouldFlush(Level lv) const { return flush_level_ >= lv; }

    void WriteToSlots(const std::string& log, Level lv);

private:
    std::string name_;
    Level level_;
    Level flush_level_;
    std::vector<SlotPtr> slots_;

private:
    static const char* kLevelNames[];
    static const char* kLevelShortNames[];
};

}//namespace base
//---------------------------------------------------------------------------
#endif //BASE_LOGGER_H_
