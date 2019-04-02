//---------------------------------------------------------------------------
#ifndef BASE_JSON_ARRAY_VALUE_H_
#define BASE_JSON_ARRAY_VALUE_H_
//---------------------------------------------------------------------------
#include "value.h"
//---------------------------------------------------------------------------
namespace base
{

namespace json
{

class BaseValue;
class ObjectValue;

class ArrayValue : public Value
{
public:
    ArrayValue();
    virtual ~ArrayValue();

public:
    size_t Size() const { return val_.array->size(); }
    void Resize(size_t size);

    void SetValue(size_t index, const Value& value);
    void SetValue(size_t index, const Value&& value);

    void Push(const Value& value);
    void Push(Value&& value);

    Value& GetValue(size_t index);
    const Value& GetValue(size_t index) const;
    BaseValue& GetBaseValue(size_t index);
    const BaseValue& GetBaseValue(size_t index) const;
    ArrayValue& GetArrayValue(size_t index);
    const ArrayValue& GetArrayValue(size_t index) const;
    ObjectValue& GetObjectValue(size_t index);
    const ObjectValue& GetObjectValue(size_t index) const;

    ArrayIter IterBegin() const { return val_.array->begin(); }
    ArrayIter IterEnd() const { return val_.array->end(); }
};

}//namespace json

}//namespace base
//---------------------------------------------------------------------------
#endif //BASE_JSON_ARRAY_VALUE_H_
