//---------------------------------------------------------------------------
#ifndef BASE_JSON_BASE_VALUE_H_
#define BASE_JSON_BASE_VALUE_H_
//---------------------------------------------------------------------------
#include "value.h"
//---------------------------------------------------------------------------
namespace base
{

namespace json
{

class BaseValue : public Value
{
public:
    BaseValue(const std::string& value);
    BaseValue(std::string&& value);
    BaseValue(const char* value);
    BaseValue(int value);
    BaseValue(int64_t value);
    BaseValue(uint64_t value);
    BaseValue(double value);
    BaseValue(bool value);
    BaseValue(const BaseValue& other);
    BaseValue(BaseValue&& other);
    BaseValue& operator=(const BaseValue& other);
    BaseValue& operator=(BaseValue&& other);
    virtual ~BaseValue();

public:
    //设置值
    void set_int(int64_t value);
    void set_uint(uint64_t value);
    void set_boolean(bool value);
    void set_double(double value);
    void set_str(const char* str);
    void set_str(const std::string& str);
    void set_str(std::string&& str);

    //获取值
    std::string& val() { return val_; }
    const std::string& val() const { return val_; }

    int64_t get_int() const;
    uint64_t get_uint() const;
    bool get_boolean()  const;
    double get_double() const;

private:
    std::string val_;
};

}//namespace json

}//namespace base
//---------------------------------------------------------------------------
#endif //BASE_JSON_ARRAY_VALUE_H_
