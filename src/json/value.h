//---------------------------------------------------------------------------
#ifndef BASE_JSON_VALUE_H_
#define BASE_JSON_VALUE_H_
//---------------------------------------------------------------------------
#include <vector>
#include <map>
#include <string>
//---------------------------------------------------------------------------
namespace base
{

namespace json
{

class Value
{
public:
    //Value的类型
    enum TYPE
    {
        NUL,        //空对象
        KEY,        //json key
        OBJECT,     //对象类型
        ARRAY,      //数组类型
        STRING,     //字符串对象
        INT,        //有符号整形
        UINT,       //无符号整形
        REAL,       //浮点型
        NUMBER,     //数字类型(INT,UINT,REAL)
        BOOLEAN,    //布伦
    };

    //类型定义
    using Array     = std::vector<Value>;
    using Object    = std::map<std::string, Value>;
    using ArrayIter = Array::const_iterator;
    using ObjectIter= Object::const_iterator;

public:
    Value(TYPE type);
    Value(const Value& other);
    Value(Value&& other);
    Value& operator=(const Value& other);
    Value& operator=(Value&& other);
    virtual ~Value();

public:
    TYPE type() const { return type_; }
    void set_type(TYPE type);

//输出Value字符串值
public:
    std::string ToString(bool format=false);

protected:
    TYPE type_;
    union
    {
        std::string* value;
        Object* object;
        Array* array;
    }val_;
};

}//namespace json

}//namespace base
//---------------------------------------------------------------------------
#endif //BASE_JSON_VALUE_H_
