//---------------------------------------------------------------------------
#ifndef BASE_JSON_OBJECT_VALUE_H_
#define BASE_JSON_OBJECT_VALUE_H_
//---------------------------------------------------------------------------
#include "value.h"
//---------------------------------------------------------------------------
namespace base
{

namespace json
{

class BaseValue;
class ArrayValue;

class ObjectValue : public Value
{
public:
    ObjectValue();
    virtual ~ObjectValue();

public:
    size_t  Size() const { return val_.object->size(); }

    Value& Put(const std::string& key, const Value& value);
    Value& Put(std::string&& key, const Value& value);
    Value& Put(const char* key, const Value& value);
    Value& Put(const std::string& key, Value&& value);
    Value& Put(std::string&& key, Value&& value);
    Value& Put(const char* key, Value&& value);

    bool Del(const std::string& key);
    bool Del(const char* key);

    bool GetValue(const std::string& key, Value& value) const;
    bool GetValue(const char* key, Value& value) const;
    bool Get(const std::string& key, BaseValue& value) const;
    bool Get(const char* key, BaseValue& value) const;
    bool Get(const std::string& key, ArrayValue& value) const;
    bool Get(const char* key, ArrayValue& value) const;
    bool Get(const std::string& key, ObjectValue& value) const;
    bool Get(const char* key, ObjectValue& value) const;

    ObjectIter IterBegin() const { return val_.object->begin(); }
    ObjectIter IterEnd() const { return val_.object->end(); }

//重载[]操作符
public:
    Value& operator[] (const char* key);
    Value& operator[] (const std::string& key);
    const Value& operator[] (const char* key) const;
    const Value& operator[] (const std::string& key) const;

};

}//namespace json

}//namespace base
//---------------------------------------------------------------------------
#endif //BASE_JSON_OBJECT_VALUE_H_
