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
ArrayValue::ArrayValue()
:   Value(TYPE::ARRAY)
{
    return;
}
//---------------------------------------------------------------------------
ArrayValue::~ArrayValue()
{
    return;
}
//---------------------------------------------------------------------------
void ArrayValue::Resize(size_t size)
{
    val_.array->resize(size);
    return;
}
//---------------------------------------------------------------------------
void ArrayValue::SetValue(size_t index, const Value& value)
{
    val_.array->at(index) = value;
    return;
}
//---------------------------------------------------------------------------
void ArrayValue::SetValue(size_t index, const Value&& value)
{
    val_.array->at(index) = std::move(value);
    return;
}
//---------------------------------------------------------------------------
void ArrayValue::Push(const Value& value)
{
    val_.array->push_back(value);
    return;
}
//---------------------------------------------------------------------------
void ArrayValue::Push(Value&& value)
{
    val_.array->push_back(std::move(value));
    return;
}
Value& ArrayValue::GetValue(size_t index)
{
    return val_.array->at(index);
}
//---------------------------------------------------------------------------
const Value& ArrayValue::GetValue(size_t index) const
{
    return val_.array->at(index);
}
//---------------------------------------------------------------------------
BaseValue& ArrayValue::GetBaseValue(size_t index)
{
    Value& value = val_.array->at(index);
    return *dynamic_cast<BaseValue*>(&value);
}
//---------------------------------------------------------------------------
const BaseValue& ArrayValue::GetBaseValue(size_t index) const
{
    const Value& value = val_.array->at(index);
    return *dynamic_cast<const BaseValue*>(&value);
}
//---------------------------------------------------------------------------
ArrayValue& ArrayValue::GetArrayValue(size_t index)
{
    Value& value = val_.array->at(index);
    return *dynamic_cast<ArrayValue*>(&value);
}
//---------------------------------------------------------------------------
const ArrayValue& ArrayValue::GetArrayValue(size_t index) const
{
    const Value& value = val_.array->at(index);
    return *dynamic_cast<const ArrayValue*>(&value);
}
//---------------------------------------------------------------------------
ObjectValue& ArrayValue::GetObjectValue(size_t index)
{
    Value& value = val_.array->at(index);
    return *dynamic_cast<ObjectValue*>(&value);
}
//---------------------------------------------------------------------------
const ObjectValue& ArrayValue::GetObjectValue(size_t index) const
{
    const Value& value = val_.array->at(index);
    return *dynamic_cast<const ObjectValue*>(&value);
}
//---------------------------------------------------------------------------
Value& ArrayValue::operator[](int index)
{
    return (*val_.array)[index];
}
//---------------------------------------------------------------------------
const Value& ArrayValue::operator[](int index) const
{
    return (*val_.array)[index];
}
//---------------------------------------------------------------------------

}//namespace json

}//namespace base
