//---------------------------------------------------------------------------
#ifndef JSON_SRC_VALUE_H_
#define JSON_SRC_VALUE_H_
//---------------------------------------------------------------------------
#include <inttypes.h>
#include <vector>
#include <map>
#include <string>
#include <assert.h>
//---------------------------------------------------------------------------
namespace base
{

namespace json
{

class Value
{
public:
    //Value的类型
    enum ValueType
    {
        Object,     //对象类型
        Array,      //数组类型
        String,     //字符串对象
        Int,        //有符号整形
        UInt,       //无符号整形
        Real,       //浮点型
        Number,     //数字类型(Int,UInt,Real)
        Boolean,    //布伦
        Null,       //空
        Key         //key，供解析用
    };

    //类型定义
    using ArrayValue        = std::vector<Value>;
    using ObjectValue       = std::map<std::string, Value>;
    using ArrayValueIter    = ArrayValue::const_iterator;
    using ObjectValueIter   = ObjectValue::const_iterator;

public:
    Value(ValueType type=ValueType::Null);
    Value(const std::string& value);
    Value(std::string&& value);
    Value(const char* value);
    Value(int value);
    Value(int64_t value);
    Value(uint64_t value);
    Value(double value);
    Value(bool value);
    Value(const Value& other);
    Value(Value&& other);
    Value& operator=(const Value& other);
    Value& operator=(Value&& other);
    ~Value();

    void Swap(Value& other);

public:
    ValueType type() const { return type_; }

    void set_int(int64_t value);
    void set_uint(uint64_t value);
    void set_boolean(bool value);
    void set_double(double value);
    void set_str(const char* str);
    void set_str(const std::string& str);
    void set_str(std::string&& str);

    int AsInt() const;
    int64_t AsInt64() const;
    unsigned int AsUInt() const;
    uint64_t AsUInt64() const;
    bool AsBoolean() const;
    float AsFloat() const;
    double AsDouble() const;
    std::string& AsString();
    const std::string& AsString() const;

    //ObjectValue
    Value& ObjectAdd(const std::string& key, const Value& value);
    Value& ObjectAdd(std::string&& key, const Value& value);
    Value& ObjectAdd(const char* key, const Value& value);
    Value& ObjectAdd(const std::string& key, Value&& value);
    Value& ObjectAdd(std::string&& key, Value&& value);
    Value& ObjectAdd(const char* key, Value&& value);

    bool ObjectDel(const std::string& key);
    bool ObjectDel(const char* key);

    bool ObjectGet(const std::string& key, Value* value) const;
    bool ObjectGet(const char* key, Value* value) const;

    size_t ObjectSize() const;

    ObjectValueIter ObjectIterBegin() const { return value_.object_->begin(); }
    ObjectValueIter ObjectIterEnd() const { return value_.object_->end(); }

    //array
    void ArrayResize(size_t size);
    size_t ArraySize() const;

    void ArraySet(size_t index, const Value& value);
    void ArraySet(size_t index, const Value&& value);

    Value& ArrayGet(size_t index);
    const Value& ArrayGet(size_t index) const;

    void ArrayAdd(const Value& value);
    void ArrayAdd(Value&& value);

    ArrayValueIter ArrayIterBegin() const { return value_.array_->begin(); }
    ArrayValueIter ArrayIterEnd() const { return value_.array_->end(); }

//重载[]操作符
public:
    Value& operator[](const char* key);
    Value& operator[](const std::string& key);
    const Value& operator[](const char* key) const;
    const Value& operator[](const std::string& key) const;

    Value& operator[](unsigned int index); //参数类型原本为size_t,但是index=0和上面的const char* 有冲突，所以定义为int
    const Value& operator[](int index) const;

//输出Value字符串值
public:
    std::string ToString(bool format=false);

private:
    void InitPayload(ValueType type);
    void DupPayload(const Value& other);
    void ReleasePayload();

    void set_type(ValueType type);

private:
    ValueType type_;
    union ValueHolder
    {
        int64_t int_;
        uint64_t uint_;
        double real_;
        bool bool_;
        std::string* string_;
        ArrayValue* array_;
        ObjectValue* object_;
    }value_;
};

}//namespace json

}//namespace base
//---------------------------------------------------------------------------
#endif //JSON_SRC_VALUE_H_
