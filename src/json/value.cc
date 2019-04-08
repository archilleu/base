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
    assert(type() == ValueType::Int);
    value_.int_ = value;
}
//---------------------------------------------------------------------------
void Value::set_uint(uint64_t value)
{
    assert(type() == ValueType::UInt);
    value_.uint_ = value;
}
//---------------------------------------------------------------------------
void Value::set_boolean(bool value)
{
    assert(type() == ValueType::Boolean);
    value_.bool_ = value;
}

//---------------------------------------------------------------------------
void Value::set_double(double value)
{
    assert(type() == ValueType::Real);
    value_.real_ = value;
}
//---------------------------------------------------------------------------
void Value::set_str(const char* str)
{
    assert(type() == ValueType::String);
    *value_.string_ = str;
}
//---------------------------------------------------------------------------
void Value::set_str(const std::string& str)
{
    assert(type() == ValueType::String);
    *value_.string_ = str;
}
//---------------------------------------------------------------------------
void Value::set_str(std::string&& str)
{
    assert(type() == ValueType::String);
    *value_.string_ = std::move(str);
}
//---------------------------------------------------------------------------
void Value::set_key(const char* str)
{
    assert(type() == ValueType::Key);
    *value_.string_ = str;
}
//---------------------------------------------------------------------------
void Value::set_key(const std::string& str)
{
    assert(type() == ValueType::Key);
    *value_.string_ = str;
}
//---------------------------------------------------------------------------
void Value::set_key(std::string&& str)
{
    assert(type() == ValueType::Key);
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
    assert(type() == ValueType::Int);
    return static_cast<int>(value_.int_);
}
//---------------------------------------------------------------------------
int64_t Value::AsInt64() const
{
    assert(type() == ValueType::Int);
    return value_.int_;
}
//---------------------------------------------------------------------------
unsigned int Value::AsUInt() const
{
    assert(type() == ValueType::UInt);
    return static_cast<unsigned int>(value_.uint_);
}
//---------------------------------------------------------------------------
uint64_t Value::AsUInt64() const
{
    assert(type() == ValueType::UInt);
    return value_.uint_;
}
//---------------------------------------------------------------------------
bool Value::AsBoolean() const
{
    assert(type() == ValueType::Boolean);
    return value_.bool_;
}
//---------------------------------------------------------------------------
float Value::AsFloat() const
{
    assert(type() == ValueType::Real);
    return static_cast<float>(value_.real_);
}
//---------------------------------------------------------------------------
double Value::AsDouble() const
{
    assert(type() == ValueType::Real);
    return value_.real_;
}
//---------------------------------------------------------------------------
std::string& Value::AsString()
{
    assert(type() == ValueType::String);
    return *value_.string_;
}
//---------------------------------------------------------------------------
const std::string& Value::AsString() const
{
    assert(type() == ValueType::String);
    return *value_.string_;
}
//---------------------------------------------------------------------------
std::string& Value::AsKey()
{
    assert(type() == ValueType::Key);
    return *value_.string_;
}
//---------------------------------------------------------------------------
const std::string& Value::AsKey() const
{
    assert(type() == ValueType::Key);
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
Value& Value::ObjectAdd(const std::string& key, const Value& value)
{
    return ObjectAdd(std::string(key), Value(value));
}
//---------------------------------------------------------------------------
Value& Value::ObjectAdd(std::string&& key, const Value& value)
{
    return ObjectAdd(std::string(key), Value(value));
}
//---------------------------------------------------------------------------
Value& Value::ObjectAdd(const char* key, const Value& value)
{
    return ObjectAdd(std::string(key), Value(value));
}
//---------------------------------------------------------------------------
Value& Value::ObjectAdd(const std::string& key, Value&& value)
{
    return ObjectAdd(std::string(key), std::move(value));
}
//---------------------------------------------------------------------------
Value& Value::ObjectAdd(std::string&& key, Value&& value)
{
    assert(type() == ValueType::Object);

    auto& ret = (*value_.object_)[std::move(key)];
    ret = std::move(value);
    return ret;
}
//---------------------------------------------------------------------------
Value& Value::ObjectAdd(const char* key, Value&& value)
{
    return ObjectAdd(std::string(key), std::move(value));
}
//---------------------------------------------------------------------------
bool Value::ObjectDel(const std::string& key)
{
    return ObjectDel(key.c_str());
}
//---------------------------------------------------------------------------
bool Value::ObjectDel(const char* key)
{
    assert(type() == ValueType::Object);

    size_t nums = value_.object_->erase(key);
    return (1 == nums);
}
//---------------------------------------------------------------------------
bool Value::ObjectGet(const std::string& key, Value& value) const
{
    return ObjectGet(key.c_str(), value);
}
//---------------------------------------------------------------------------
bool Value::ObjectGet(const char* key, Value& value) const
{
    assert(type() == ValueType::Object);

    auto iter = value_.object_->find(key);
    if(value_.object_->end() == iter)
        return false;

    value = iter->second;
    return true;
}
//---------------------------------------------------------------------------
void Value::ArrayResize(size_t size)
{
    assert(type() == ValueType::Array);

    value_.array_->resize(size);
    return;
}
//---------------------------------------------------------------------------
void Value::ArraySet(size_t index, const Value& value)
{
    ArraySet(index, Value(value));
    return;
}
//---------------------------------------------------------------------------
void Value::ArraySet(size_t index, const Value&& value)
{
    assert(type() == ValueType::Array);

    value_.array_->at(index) = std::move(value);
    return;
}
//---------------------------------------------------------------------------
Value& Value::ArrayGet(size_t index)
{
    assert(type() == ValueType::Array);

    return value_.array_->at(index);
}
//---------------------------------------------------------------------------
const Value& Value::ArrayGet(size_t index) const
{
    assert(type() == ValueType::Array);

    return value_.array_->at(index); 
}
//---------------------------------------------------------------------------
void Value::ArrayAdd(const Value& value)
{
    ArrayAdd(Value(value));
    return;
}
//---------------------------------------------------------------------------
void Value::ArrayAdd(Value&& value)
{
    assert(type() == ValueType::Array);

    value_.array_->push_back(std::move(value));
    return;
}
//---------------------------------------------------------------------------
Value& Value::operator[](const char* key)
{
    assert(type() == ValueType::Object);
    
    Value& value = (*value_.object_)[key];
    return value;
}
//---------------------------------------------------------------------------
Value& Value::operator[](const std::string& key)
{
    assert(type() == ValueType::Object);
    
    Value& value = (*value_.object_)[key];
    return value;
}
//---------------------------------------------------------------------------
const Value& Value::operator[](const char* key) const
{
    assert(type() == ValueType::Object);
    
    const Value& value = (*value_.object_)[key];
    return value;
}
//---------------------------------------------------------------------------
const Value& Value::operator[](const std::string& key) const
{
    assert(type() == ValueType::Object);
    
    const Value& value = (*value_.object_)[key];
    return value;
}
//---------------------------------------------------------------------------
Value& Value::operator[](unsigned int index)
{
    assert(type() == ValueType::Array);

    return (*value_.array_)[index];
}
//---------------------------------------------------------------------------
const Value& Value::operator[](int index) const
{
    assert(type() == ValueType::Array);

    return (*value_.array_)[index];
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
