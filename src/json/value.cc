//---------------------------------------------------------------------------
#include "value.h"
#include "json_writer.h"
//---------------------------------------------------------------------------
namespace base
{

namespace json
{
//---------------------------------------------------------------------------
Value::Value()
:   type_(TYPE::NUL)
{
    val_.value = nullptr;
    val_.array = nullptr;
    val_.object = nullptr;
}
//---------------------------------------------------------------------------
Value::Value(TYPE type)
:   type_(type)
{
    switch(type_)
    {
        case OBJECT:
            val_.object = new Object();
            val_.value = nullptr;
            val_.array = nullptr;
            break;

        case ARRAY:
            val_.array = new Array();
            val_.value = nullptr;
            val_.object = nullptr;
            break;

        default:
            val_.value = new std::string();
            val_.array = nullptr;
            val_.object = nullptr;
    }

    return;
}
//---------------------------------------------------------------------------
Value::Value(const Value& other)
{
    *this = other;
    return;
}
//---------------------------------------------------------------------------
Value::Value(Value&& other)
{
    *this = std::move(other);
    return;
}
//---------------------------------------------------------------------------
Value& Value::operator=(const Value& other)
{
    type_ = other.type_;
    val_ = other.val_;
    return *this;
}
//---------------------------------------------------------------------------
Value& Value::operator=(Value&& other)
{
    type_ = other.type_;
    val_ = std::move(other.val_);
    return *this;
}
//---------------------------------------------------------------------------
Value::~Value()
{
    switch(type_)
    {
        case OBJECT:
            delete val_.object;
            break;

        case ARRAY:
            delete val_.array;
            break;

        default:
            delete val_.value;
    }

    return;
}
//---------------------------------------------------------------------------
void Value::set_type(TYPE type)
{
    type_ = type;

    switch(type_)
    {
        case OBJECT:
            val_.object = new Object();
            break;

        case ARRAY:
            val_.array = new Array();
            break;

        default:
            val_.value = new std::string();
    }

    return;
}
//---------------------------------------------------------------------------
}//namespace json

}//namespace base
