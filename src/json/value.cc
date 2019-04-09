//---------------------------------------------------------------------------
#define __STDC_FORMAT_MACROS
//---------------------------------------------------------------------------
#include <algorithm>
#include <assert.h>
#include "value.h"
#include "json_writer.h"
//---------------------------------------------------------------------------
namespace base
{

namespace json
{

//---------------------------------------------------------------------------
const Value Value::NullValue;
//---------------------------------------------------------------------------
Value::Value(ValueType type)
{
    InitPayload(type);
    return;
}
//---------------------------------------------------------------------------
Value::Value(const std::string& value)
{
    InitPayload(ValueType::String);
    *value_.string_ = value;
    return;
}
//---------------------------------------------------------------------------
Value::Value(std::string&& value)
{
    InitPayload(ValueType::String);
    *value_.string_ = std::move(value);
    return;
}
//---------------------------------------------------------------------------
Value::Value(const char* value)
{
    InitPayload(ValueType::String);
    *value_.string_ = value;
    return;
}
//---------------------------------------------------------------------------
Value::Value(int value)
{
    InitPayload(ValueType::Int);
    value_.int_ = value;
    return;
}
//---------------------------------------------------------------------------
Value::Value(int64_t value)
{
    InitPayload(ValueType::Int);
    value_.int_ = value;
    return;
}
//---------------------------------------------------------------------------
Value::Value(unsigned int value)
{
    InitPayload(ValueType::UInt);
    value_.uint_ = value;
    return;
}
//---------------------------------------------------------------------------
Value::Value(uint64_t value)
{
    InitPayload(ValueType::UInt);
    value_.uint_ = value;
    return;
}
//---------------------------------------------------------------------------
Value::Value(double value)
{
    InitPayload(ValueType::Real);
    value_.real_ = value;
    return;
}
//---------------------------------------------------------------------------
Value::Value(bool value)
{
    InitPayload(ValueType::Boolean);
    value_.bool_ = value;
    return;
}
//---------------------------------------------------------------------------
Value::Value(const Value& other)
{
    DupPayload(other);
    return;
}
//---------------------------------------------------------------------------
Value::Value(Value&& other)
{
    InitPayload(ValueType::Null);
    Swap(other);
    return;
}
//---------------------------------------------------------------------------
Value& Value::operator=(const Value& other)
{
    Value(other).Swap(*this);
    return *this;
}
//---------------------------------------------------------------------------
Value& Value::operator=(Value&& other)
{
    InitPayload(ValueType::Null);
    Swap(other);
    return *this;
}
//---------------------------------------------------------------------------
Value::~Value()
{
    ReleasePayload();
    type_ = ValueType::Null;
    value_.uint_ = 0;
    return;
}

//---------------------------------------------------------------------------
void Value::Swap(Value& other)
{
    std::swap(type_, other.type_);
    std::swap(value_, other.value_);
    return;
}
//---------------------------------------------------------------------------
void Value::set_int(int64_t value)
{
    if(type() != ValueType::Int)
        throw type_error();

    value_.int_ = value;
}
//---------------------------------------------------------------------------
void Value::set_uint(uint64_t value)
{
    if(type() != ValueType::UInt)
        throw type_error();

    value_.uint_ = value;
}
//---------------------------------------------------------------------------
void Value::set_boolean(bool value)
{
    if(type() != ValueType::Boolean)
        throw type_error();

    value_.bool_ = value;
}
//---------------------------------------------------------------------------
void Value::set_double(double value)
{
    if(type() != ValueType::Real)
        throw type_error();

    value_.real_ = value;
}
//---------------------------------------------------------------------------
void Value::set_str(const char* str)
{
    if(type() != ValueType::String)
        throw type_error();

    *value_.string_ = str;
}
//---------------------------------------------------------------------------
void Value::set_str(const std::string& str)
{
    if(type() != ValueType::String)
        throw type_error();

    *value_.string_ = str;
}
//---------------------------------------------------------------------------
void Value::set_str(std::string&& str)
{
    if(type() != ValueType::String)
        throw type_error();

    *value_.string_ = std::move(str);
}
//---------------------------------------------------------------------------
void Value::set_key(const char* str)
{
    if(type() != ValueType::Key)
        throw type_error();

    *value_.string_ = str;
}
//---------------------------------------------------------------------------
void Value::set_key(const std::string& str)
{
    if(type() != ValueType::Key)
        throw type_error();

    *value_.string_ = str;
}
//---------------------------------------------------------------------------
void Value::set_key(std::string&& str)
{
    if(type() != ValueType::Key)
        throw type_error();

    *value_.string_ = std::move(str);
}
//---------------------------------------------------------------------------
bool Value::IsInt() const
{
    return (type()==ValueType::Int);
}
//---------------------------------------------------------------------------
bool Value::IsUInt() const
{
    return (type()==ValueType::UInt);
}
//---------------------------------------------------------------------------
bool Value::IsBoolean() const
{
    return (type()==ValueType::Boolean);
}
//---------------------------------------------------------------------------
bool Value::IsReal() const
{
    return (type()==ValueType::Real);
}
//---------------------------------------------------------------------------
bool Value::IsString() const
{
    return (type()==ValueType::String);
}
//---------------------------------------------------------------------------
bool Value::IsArray() const
{
    return (type()==ValueType::Array);
}
//---------------------------------------------------------------------------
bool Value::IsObject() const
{
    return (type()==ValueType::Object);
}
//---------------------------------------------------------------------------
bool Value::IsNull() const
{
    return (type()==ValueType::Null);
}
//---------------------------------------------------------------------------
bool Value::IsKey() const
{
    return (type()==ValueType::Key);
}
//---------------------------------------------------------------------------
int Value::AsInt() const
{
    if(type() != ValueType::Int)
        throw type_error();

    return static_cast<int>(value_.int_);
}
//---------------------------------------------------------------------------
int64_t Value::AsInt64() const
{
    if(type() != ValueType::Int)
        throw type_error();

    return value_.int_;
}
//---------------------------------------------------------------------------
unsigned int Value::AsUInt() const
{
    if(type() != ValueType::UInt)
        throw type_error();

    return static_cast<unsigned int>(value_.uint_);
}
//---------------------------------------------------------------------------
uint64_t Value::AsUInt64() const
{
    if(type() != ValueType::UInt)
        throw type_error();

    return value_.uint_;
}
//---------------------------------------------------------------------------
bool Value::AsBoolean() const
{
    if(type() != ValueType::Boolean)
        throw type_error();

    return value_.bool_;
}
//---------------------------------------------------------------------------
float Value::AsFloat() const
{
    if(type() != ValueType::Real)
        throw type_error();

    return static_cast<float>(value_.real_);
}
//---------------------------------------------------------------------------
double Value::AsDouble() const
{
    if(type() != ValueType::Real)
        throw type_error();

    return value_.real_;
}
//---------------------------------------------------------------------------
std::string& Value::AsString()
{
    if(type() != ValueType::String)
        throw type_error();

    return *value_.string_;
}
//---------------------------------------------------------------------------
const std::string& Value::AsString() const
{
    if(type() != ValueType::String)
        throw type_error();

    return *value_.string_;
}
//---------------------------------------------------------------------------
std::string& Value::AsKey()
{
    if(type() != ValueType::Key)
        throw type_error();

    return *value_.string_;
}
//---------------------------------------------------------------------------
const std::string& Value::AsKey() const
{
    if(type() != ValueType::Key)
        throw type_error();

    return *value_.string_;
}
//---------------------------------------------------------------------------
size_t Value::Size() const
{
    switch(type())
    {
        case ValueType::Object:
            return value_.object_->size();

        case ValueType::Array:
            return value_.array_->size();

        default:
            return 0;
    }
}
//---------------------------------------------------------------------------
Value& Value::operator[](const char* key)
{
    return (*this)[std::string(key)];
}
//---------------------------------------------------------------------------
Value& Value::operator[](const std::string& key)
{
    return (*this)[std::string(key)];
}
//---------------------------------------------------------------------------
Value& Value::operator[](const std::string&& key)
{
    if(type() != ValueType::Object)
        throw new type_error();
    
    return (*value_.object_)[std::move(key)];
}
//---------------------------------------------------------------------------
const Value& Value::operator[](const char* key) const
{
    if(type() != ValueType::Object)
        throw new type_error();
    
    ObjectValueIter iter = value_.object_->find(key);
    if(iter == value_.object_->end())
        return NullValue;

    return iter->second;
}
//---------------------------------------------------------------------------
const Value& Value::operator[](const std::string& key) const
{
    return (*this)[key.c_str()];
}
//---------------------------------------------------------------------------
const Value& Value::ObjectGet(const std::string& key) const
{
    return ObjectGet(key.c_str());
}
//---------------------------------------------------------------------------
const Value& Value::ObjectGet(const char* key) const
{
    if(type() != ValueType::Object)
        throw new type_error();
    
    ObjectValueIter iter = value_.object_->find(key);
    if(iter == value_.object_->end())
        return NullValue;

    return iter->second;
}
//---------------------------------------------------------------------------
bool Value::ObjectDel(const std::string& key)
{
    return ObjectDel(key.c_str());
}
//---------------------------------------------------------------------------
bool Value::ObjectDel(const char* key)
{
    if(type() != ValueType::Object)
        throw new type_error();

    size_t nums = value_.object_->erase(key);
    return (1 == nums);
}
//---------------------------------------------------------------------------
void Value::Reserver(size_t size)
{
    if(type() != ValueType::Array)
        throw type_error();

    value_.array_->reserve(size);
    return;
}
//---------------------------------------------------------------------------
Value& Value::operator[](unsigned int index)
{
    if(type() != ValueType::Array)
        throw type_error();

    if(Size() <  index)
        throw std::out_of_range("index out of range");

    return (*value_.array_)[index];
}
//---------------------------------------------------------------------------
const Value& Value::operator[](unsigned int index) const
{
    if(type() != ValueType::Array)
        throw type_error();

    if(Size() <  index)
        throw std::out_of_range("index out of range");

    return (*value_.array_)[index];
}
//---------------------------------------------------------------------------
void Value::ArrayAppend(const Value& value)
{
    ArrayAppend(Value(value));
    return;
}
//---------------------------------------------------------------------------
void Value::ArrayAppend(Value&& value)
{
    if(type() != ValueType::Array)
        throw type_error();

    value_.array_->push_back(std::move(value));
    return;
}
//---------------------------------------------------------------------------
std::string Value::ToString(bool format)
{
    return JsonWriter(*this).ToString(format);
}
//---------------------------------------------------------------------------
bool Value::operator==(const Value& other) const
{
    if(this == &other)
        return true;

    if(type() != other.type())
        return false;

    switch(type())
    {
        case ValueType::Object:
            return ((value_.object_->size()==other.value_.object_->size()) &&
                (*value_.object_==*other.value_.object_));

        case ValueType::Array:
            return ((value_.array_->size()==other.value_.array_->size()) &&
                (*value_.array_==*other.value_.array_));

        case ValueType::Key:
        case ValueType::String:
            return (*value_.string_==*other.value_.string_);

        case Boolean:
            return (value_.bool_==other.value_.bool_);

        case Int:
            return (value_.int_==other.value_.int_);

        case UInt:
            return (value_.uint_==other.value_.uint_);

        case Real:
            return (value_.real_==other.value_.real_);

        case Number:
            return ((value_.int_==other.value_.int_)||
                    (value_.uint_==other.value_.uint_)||
                    (value_.real_==other.value_.real_));
        case Null:
            return true;

        default:
            assert(0);
    }

    return false;
}
//---------------------------------------------------------------------------
void Value::InitPayload(ValueType value_type)
{
    set_type(value_type);
    switch(type())
    {
        case ValueType::Object:
            value_.object_ = new ObjectValue();
            break;

        case ValueType::Array:
            value_.array_ = new ArrayValue();
            break;

        case ValueType::Key:
        case ValueType::String:
            value_.string_ = new std::string();
            break;

        case Boolean:
            value_.bool_ = false;
            break;

        case Int:
        case UInt:
        case Real:
        case Number:
        case Null:
            break;

        default:
            assert(0);
    }
}
//---------------------------------------------------------------------------
void Value::DupPayload(const Value& other)
{
    set_type(other.type());
    switch(type())
    {
        case ValueType::Object:
            value_.object_ = new ObjectValue(*other.value_.object_);
            break;

        case ValueType::Array:
            value_.array_ = new ArrayValue(*other.value_.array_);
            break;

        case ValueType::Key:
        case ValueType::String:
            value_.string_ = new std::string(*other.value_.string_);
            break;

        case Boolean:
        case Int:
        case UInt:
        case Real:
        case Number:
        case Null:
            value_ = other.value_;
            break;

        default:
            assert(0);
    }
}
//---------------------------------------------------------------------------
void Value::ReleasePayload()
{
    switch(type())
    {
        case ValueType::Object:
            delete value_.object_;
            break;

        case ValueType::Array:
            delete value_.array_;
            break;

        case ValueType::Key:
        case ValueType::String:
            delete value_.string_;
            break;

        case Boolean:
        case Int:
        case UInt:
        case Real:
        case Number:
        case Null:
            break;

        default:
            assert(0);
    }
}
//---------------------------------------------------------------------------
void Value::set_type(ValueType type)
{
    type_ = type;

    return;
}
//---------------------------------------------------------------------------
}//namespace json

}//namespace base
