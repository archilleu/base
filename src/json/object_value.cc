//---------------------------------------------------------------------------
#include "array_value.h"
#include "base_value.h"
#include "object_value.h"
//---------------------------------------------------------------------------
namespace base
{

namespace json
{
//---------------------------------------------------------------------------
ObjectValue::ObjectValue()
:   Value(TYPE::ARRAY)
{
    return;
}
//---------------------------------------------------------------------------
ObjectValue::~ObjectValue()
{
    return;
}
//---------------------------------------------------------------------------
Value& ObjectValue::Put(const std::string& key, const Value& value)
{
    return Put(std::string(key), value);
}
//---------------------------------------------------------------------------
Value& ObjectValue::Put(std::string&& key, const Value& value)
{
    auto& val = (*val_.object)[std::move(key)];
    val = value;
    return val;
}
//---------------------------------------------------------------------------
Value& ObjectValue::Put(const char* key, const Value& value)
{
    return Put(std::string(key), value);
}
//---------------------------------------------------------------------------
Value& ObjectValue::Put(const std::string& key, Value&& value)
{
    return Put(std::string(key), std::move(value));
}
//---------------------------------------------------------------------------
Value& ObjectValue::Put(std::string&& key, Value&& value)
{
    auto& val = (*val_.object)[std::move(key)];
    val = std::move(value);
    return val;
}
//---------------------------------------------------------------------------
Value& ObjectValue::Put(const char* key, Value&& value)
{
    return Put(std::string(key), std::move(value));
}
//---------------------------------------------------------------------------
bool ObjectValue::Del(const std::string& key)
{
    return Del(key.c_str());
}
//---------------------------------------------------------------------------
bool ObjectValue::Del(const char* key)
{
    size_t nums = val_.object->erase(key);
    return (1 == nums);
}
//---------------------------------------------------------------------------
bool ObjectValue::GetValue(const std::string& key, Value& value) const
{
    return GetValue(key.c_str(), value);
}
//---------------------------------------------------------------------------
bool ObjectValue::GetValue(const char* key, Value& value) const
{
    auto iter = val_.object->find(key);
    if(val_.object->end() == iter)
        return false;

    value = iter->second;
    return true;
}
//---------------------------------------------------------------------------
bool ObjectValue::Get(const std::string& key, BaseValue& value) const
{
    return Get(key.c_str(), value);
}
//---------------------------------------------------------------------------
bool ObjectValue::Get(const char* key, BaseValue& value) const
{
    BaseValue val = *dynamic_cast<BaseValue*>(&value);
    if(false == GetValue(key, val))
        return false;
    
    return true;
}
//---------------------------------------------------------------------------
bool ObjectValue::Get(const std::string& key, ArrayValue& value) const
{
    return Get(key.c_str(), value);
}
//---------------------------------------------------------------------------
bool ObjectValue::Get(const char* key, ArrayValue& value) const
{
    ArrayValue val = *dynamic_cast<ArrayValue*>(&value);
    if(false == GetValue(key, val))
        return false;
    
    return true;
}
//---------------------------------------------------------------------------
bool ObjectValue::Get(const std::string& key, ObjectValue& value) const
{
    return Get(key.c_str(), value);
}
//---------------------------------------------------------------------------
bool ObjectValue::Get(const char* key, ObjectValue& value) const
{
    ObjectValue val = *dynamic_cast<ObjectValue*>(&value);
    if(false == GetValue(key, val))
        return false;
    
    return true;
}
//---------------------------------------------------------------------------
Value& ObjectValue::operator[](const char* key)
{
    Value& value = (*val_.object)[key];
    return value;
}
//---------------------------------------------------------------------------
Value& ObjectValue::operator[](const std::string& key)
{
    Value& value = (*val_.object)[key];
    return value;
}
//---------------------------------------------------------------------------
const Value& ObjectValue::operator[](const char* key) const
{
    const Value& value = (*val_.object)[key];
    return value;
}
//---------------------------------------------------------------------------
const Value& ObjectValue::operator[](const std::string& key) const
{
    const Value& value = (*val_.object)[key];
    return value;
}
//---------------------------------------------------------------------------

}//namespace json

}//namespace base
