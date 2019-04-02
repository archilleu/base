//---------------------------------------------------------------------------
#include "base_value.h"
//---------------------------------------------------------------------------
namespace base
{

namespace json
{
//---------------------------------------------------------------------------
BaseValue::BaseValue(const std::string& value)
:val_(value)
{
    type_ = TYPE::STRING;
    return;
}
//---------------------------------------------------------------------------
BaseValue::BaseValue(std::string&& value)
:   val_(std::move(value))
{
    type_ = TYPE::STRING;
    return;
}
//---------------------------------------------------------------------------
BaseValue::BaseValue(const char* value)
:   val_(value)
{
    type_ = TYPE::STRING;
    return;
}
//---------------------------------------------------------------------------
BaseValue::BaseValue(int value)
{
    type_ = TYPE::INT;
    set_int(value);
    return;
}
//---------------------------------------------------------------------------
BaseValue::BaseValue(int64_t value)
{
    type_ = TYPE::INT;
    set_int(value);
    return;
}
//---------------------------------------------------------------------------
BaseValue::BaseValue(uint64_t value)
{
    type_ = TYPE::UINT;
    set_uint(value);
    return;
}
//---------------------------------------------------------------------------
BaseValue::BaseValue(double value)
{
    type_ = TYPE::REAL;
    set_double(value);
    return;
}
//---------------------------------------------------------------------------
BaseValue::BaseValue(bool value)
{
    type_ = TYPE::BOOLEAN;
    set_boolean(value);
    return;
}
//---------------------------------------------------------------------------
BaseValue::BaseValue(const BaseValue& other)
{
    *this = other;
    return;
}
//---------------------------------------------------------------------------
BaseValue::BaseValue(BaseValue&& other)
{
    *this = std::move(other);
}
//---------------------------------------------------------------------------
BaseValue& BaseValue::operator=(const BaseValue& other)
{
    type_ = other.type_;
    val_ = other.val_;
    return *this;
}
//---------------------------------------------------------------------------
BaseValue& BaseValue::operator=(BaseValue&& other)
{
    type_ = other.type_;
    other.type_ = TYPE::NUL;
    val_ = std::move(other.val_);
    return *this;
}
//---------------------------------------------------------------------------
BaseValue::~BaseValue()
{
    return;
}
//---------------------------------------------------------------------------
void BaseValue::set_int(int64_t value)
{
    assert(INT == type_);
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "%" PRId64 "", value);
    val_ = buffer;
}
//---------------------------------------------------------------------------
void BaseValue::set_uint(uint64_t value)
{
    assert(UINT == type_);
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "%" PRIu64 "", value);
    val_ = buffer;
}
//---------------------------------------------------------------------------
void BaseValue::set_boolean(bool value)
{
    assert(BOOLEAN == type_);
    value ? (val_="true") : (val_="false");
}
//---------------------------------------------------------------------------
void BaseValue::set_double(double value)
{
//---------------------------------------------------------------------------
    assert(REAL == type_);
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "%.7lf", value);
    val_ = buffer;
}
//---------------------------------------------------------------------------
void BaseValue::set_str(const char* str)
{
    if((STRING!=type_) && (KEY!=type_))
    {
        assert(0);
        return;
    }

    val_ = str;
}
//---------------------------------------------------------------------------
void BaseValue::set_str(const std::string& str)
{
    if((STRING!=type_) && (KEY!=type_))
    {
        assert(0);
        return;
    }
    
    val_ = str;
}
//---------------------------------------------------------------------------
void BaseValue::set_str(std::string&& str)
{
    if((STRING!=type_) && (KEY!=type_))
    {
        assert(0);
        return;
    }

    val_ = str;
}
//---------------------------------------------------------------------------
int64_t BaseValue::get_int() const
{
    assert(INT == type_);
    return std::stoll(val_);
}
//---------------------------------------------------------------------------
uint64_t BaseValue::get_uint() const
{
    assert(UINT == type_);
    return std::stoull(val_);
}
//---------------------------------------------------------------------------
bool BaseValue::get_boolean() const
{
    assert(BOOLEAN == type_);
    return (val_ == "true");
}
//---------------------------------------------------------------------------
double BaseValue::get_double() const
{
    assert(REAL == type_);
    return std::stod(val_);
}
//---------------------------------------------------------------------------

}//namespace json

}//namespace base
