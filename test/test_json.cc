//---------------------------------------------------------------------------
#include "test_inc.h"
#include "../src/json/json.h"
#include "../src/json/token_reader.h"
#include "../src/json/char_reader.h"
#include "../src/function.h"
#include <stdio.h>
#include <fstream>
#include <dirent.h>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>
#include <float.h>
//---------------------------------------------------------------------------
using namespace base;
using namespace base::test;
using namespace json;
//---------------------------------------------------------------------------
bool Test_Value_Base()
{
    {
    //基本操作
    {
    Value value_none;
    TEST_ASSERT(value_none.IsNull());
    TEST_ASSERT(value_none.type()==Value::ValueType::Null);
    Value value_none1;
    TEST_ASSERT(value_none == value_none1);
    }

    {
    const char* c_str = "key";
    Value value(Value::Key);
    TEST_ASSERT(Value::Key == value.type());
    TEST_ASSERT(value.IsKey());
    value.set_key(c_str);
    TEST_ASSERT(value.AsKey() == std::string(c_str));
    Value value1(Value::Key);
    value1.set_key(c_str);
    TEST_ASSERT(value == value1);
    }

    {
    const char* c_str = "string";
    Value value(Value::String);
    TEST_ASSERT(Value::String == value.type());
    TEST_ASSERT(value.IsString());
    value.set_str(c_str);
    TEST_ASSERT(value.AsString() == std::string(c_str));
    Value value1(c_str);
    TEST_ASSERT(value == value1);

    std::string move_str = "string";
    Value value_move(std::move(move_str));
    TEST_ASSERT(value.AsString() == "string");
    TEST_ASSERT(move_str.empty());

    move_str = "string";
    value_move.set_str(std::move(move_str));
    TEST_ASSERT(value.AsString() == "string");
    TEST_ASSERT(move_str.empty());
    }

    {
    const int64_t val = 0x7FFFFFFFFFFFFFFF;
    Value value(Value::Int);
    TEST_ASSERT(Value::Int == value.type());
    TEST_ASSERT(value.IsInt());
    value.set_int(val);
    TEST_ASSERT(value.AsInt64() == val);
    Value value1(val);
    TEST_ASSERT(value == value1);

    const int val32 = 0x7FFFFFFF;
    Value value32(Value::Int);
    TEST_ASSERT(Value::Int == value32.type());
    TEST_ASSERT(value32.IsInt());
    value32.set_int(val32);
    TEST_ASSERT(value32.AsInt() == val32);
    Value value321(val32);
    TEST_ASSERT(value32 == value321);

    const uint64_t val_ = 0xFFFFFFFFFFFFFFFF;
    Value value_(Value::UInt);
    TEST_ASSERT(Value::UInt == value_.type());
    TEST_ASSERT(value_.IsUInt());
    value_.set_uint(val_);
    TEST_ASSERT(value_.AsUInt64() == val_);
    Value value_1(val_);
    TEST_ASSERT(value_ == value_1);

    const unsigned int val32_ = 0xFFFFFFFF;
    Value value32_(Value::UInt);
    TEST_ASSERT(Value::UInt == value32_.type());
    TEST_ASSERT(value32_.IsUInt());
    value32_.set_uint(val32_);
    TEST_ASSERT(value32_.AsUInt() == val32_);
    Value value321_(val32_);
    TEST_ASSERT(value32_ == value321_);
    }

    {
    const double d = 1.0;
    Value value(Value::Real);
    TEST_ASSERT(Value::Real == value.type());
    TEST_ASSERT(value.IsReal());
    value.set_double(d);
    TEST_ASSERT(value.AsDouble() == d);
    Value value1(d);
    TEST_ASSERT(value == value1);
    }

    {
    const bool b = true;
    Value value(Value::Boolean);
    TEST_ASSERT(Value::Boolean == value.type());
    TEST_ASSERT(value.IsBoolean());
    value.set_boolean(b);
    TEST_ASSERT(value.AsBoolean() == b);
    Value value1(b);
    TEST_ASSERT(value == value1);
    }

    {
    //复制构造
    Value val_ori("orgin");
    Value val_copy(val_ori);
    TEST_ASSERT(val_ori == val_copy);
    }

    {
    //=
    Value val_ori("orgin");
    Value val_assg = val_ori;
    TEST_ASSERT(val_ori == val_assg);
    }

    {
    //move
    Value val_ori("orgin");
    Value val_move(std::move(val_ori));
    TEST_ASSERT(val_ori.type() == Value::ValueType::Null);
    TEST_ASSERT(val_move.type() == Value::ValueType::String);
    }

    {
    //move==
    Value val_ori("orgin");
    Value val_move_assg = std::move(val_ori);
    TEST_ASSERT(val_ori.type() == Value::ValueType::Null);
    TEST_ASSERT(val_move_assg.type() == Value::ValueType::String);
    }

    }

    {
    //异常操作
    Value v_exception;
    try
    {
        v_exception.set_int(1);
        TEST_ASSERT(false);
    }catch(type_error e)
    {
    }
    try
    {
        v_exception.set_uint(1);
        TEST_ASSERT(false);
    }catch(type_error e)
    {
    }
    try
    {
        v_exception.set_boolean(1);
        TEST_ASSERT(false);
    }catch(type_error e)
    {
    }
    try
    {
        v_exception.set_double(1);
        TEST_ASSERT(false);
    }catch(type_error e)
    {
    }
    try
    {
        v_exception.set_str("aaa");
        TEST_ASSERT(false);
    }catch(type_error e)
    {
    }
    try
    {
        v_exception.set_str("aaa");
        TEST_ASSERT(false);
    }catch(type_error e)
    {
    }
    try
    {
        v_exception.set_str(std::string("aaa"));
        TEST_ASSERT(false);
    }catch(type_error e)
    {
    }
    try
    {
        v_exception.set_key("key");
        TEST_ASSERT(false);
    }catch(type_error e)
    {
    }
    try
    {
        v_exception.set_key(std::string("key"));
        TEST_ASSERT(false);
    }catch(type_error e)
    {
    }


    try
    {
        v_exception.AsInt();
        TEST_ASSERT(false);
    }catch(type_error e)
    {
    }
    try
    {
        v_exception.AsInt64();
        TEST_ASSERT(false);
    }catch(type_error e)
    {
    }
    try
    {
        v_exception.AsUInt();
        TEST_ASSERT(false);
    }catch(type_error e)
    {
    }
    try
    {
        v_exception.AsUInt64();
        TEST_ASSERT(false);
    }catch(type_error e)
    {
    }
    try
    {
        v_exception.AsBoolean();
        TEST_ASSERT(false);
    }catch(type_error e)
    {
    }
    try
    {
        v_exception.AsFloat();
        TEST_ASSERT(false);
    }catch(type_error e)
    {
    }
    try
    {
        v_exception.AsDouble();
        TEST_ASSERT(false);
    }catch(type_error e)
    {
    }
    try
    {
        v_exception.AsString();
        TEST_ASSERT(false);
    }catch(type_error e)
    {
    }
    try
    {
        v_exception.AsKey();
        TEST_ASSERT(false);
    }catch(type_error e)
    {
    }
    }

    return true;
}
//---------------------------------------------------------------------------
bool Test_Value_Obj()
{
    //object
    {
    Value value_none(Value::Object);
    TEST_ASSERT(value_none.type() == Value::Object);
    TEST_ASSERT(value_none.IsObject());
    TEST_ASSERT(value_none.Size() == 0);
    Value& v1 = value_none["v1"];
    TEST_ASSERT(v1.type() == Value::Null);
    v1 = Value("k1");
    TEST_ASSERT(value_none.Size() == 1);
    v1 = value_none["v1"];
    TEST_ASSERT(v1.AsString() == "k1");
    TEST_ASSERT(false == value_none.ObjectDel("none"));
    TEST_ASSERT(false == value_none.ObjectDel(std::string("none")));

    const Value value(Value::Object);
    TEST_ASSERT(value.type() == Value::Object);

    //初始状态
    TEST_ASSERT(0 == value.Size());

    const Value& v = value["none"];
    TEST_ASSERT(Value::NullValue == v);
    size_t count = 0;
    for(auto iter=value.ObjectIterBegin(); value.ObjectIterEnd()!=iter; ++iter)
        count++;
    TEST_ASSERT(0 == count);

    const Value& v3 = value.ObjectGet("none");
    TEST_ASSERT(Value::NullValue == v3);
    count = 0;
    for(auto iter=value.ObjectIterBegin(); value.ObjectIterEnd()!=iter; ++iter)
        count++;
    TEST_ASSERT(0 == count);
    }

    //添加Object
    Value value(Value::Object);
    {
    Value v0;
    Value v1 = -1;
    Value v2 = 1;
    Value v3 = 1.1;
    Value v4 = true;
    Value v5 = false;
    Value v6 = "string";
    Value v7(Value::Object);
    Value v8(Value::Array);

    value["key0"] = v0;
    value["key1"] = std::move(v1);
    value[std::string("key2")] = std::move(v2);
    std::string key3 = "key3";
    value[key3] = std::move(v3);
    value["key4"] = std::move(v4);
    value[std::string("key5")] = std::move(v5);
    std::string key6 = "key6";
    value[std::move(key6)] = std::move(v6);
    value["key7"] = std::move(v7);
    value["key8"] = std::move(v8);

    size_t size = value.Size();
    TEST_ASSERT(9 == size);
    }

    {
    //检查添加的元素
    const Value& v0 = value["key0"];
    TEST_ASSERT(v0.IsNull());

    const Value& v1 = value["key1"];
    TEST_ASSERT(v1.AsInt() == -1);

    const Value& v2 = value[std::string("key2")];
    TEST_ASSERT(v2.AsInt() == 1);

    const Value& v3 = value["key3"];
    TEST_ASSERT((v3.AsDouble() - 1.1) < 0.01);

    const Value& v4 = value["key4"];
    TEST_ASSERT(v4.AsBoolean() == true);

    const Value& v5 = value["key5"];
    TEST_ASSERT(v5.AsBoolean() == false);

    Value& v6 = value["key6"];
    TEST_ASSERT(v6.AsString() == "string");
    const char* new_string = "new string";
    v6.set_str(new_string);
    const Value& v61 = value["key6"];
    TEST_ASSERT(new_string == v61.AsString());

    const Value& v7 = value["key7"];
    TEST_ASSERT(v7.IsObject());

    const Value& v8 = value["key8"];
    TEST_ASSERT(v8.IsArray());

    for(auto iter=value.ObjectIterBegin(); value.ObjectIterEnd()!=iter; ++iter)
    {
        //FIXME:shuchustirng
        //std::cout << "key:" << iter->first << " value:" << iter->second.val() << std::endl;
    }

    //添加同样key值的会被覆盖
    Value v1_cover = 2;
    value["key1"] =  std::move(v1_cover);
    const Value& v1_cover_get = value["key1"];
    TEST_ASSERT(v1_cover_get.AsInt() == 2);

    //删除key值
    TEST_ASSERT(value.ObjectDel("key0"));
    TEST_ASSERT(value.ObjectDel("key1"));
    TEST_ASSERT(value.ObjectDel("key2"));
    TEST_ASSERT(value.ObjectDel("key3"));
    TEST_ASSERT(value.ObjectDel("key4"));
    TEST_ASSERT(value.ObjectDel("key5"));
    TEST_ASSERT(value.ObjectDel("key6"));
    TEST_ASSERT(value.ObjectDel("key7"));
    TEST_ASSERT(value.ObjectDel("key8"));

    TEST_ASSERT(0 == value.Size());
    for(auto iter=value.ObjectIterBegin(); value.ObjectIterEnd()!=iter; ++iter)
    {
        //没有元素
        assert(0);
    }
    }

    //拷贝构造等等
    {
    Value val_ori(Value::Object);
    Value v1(Value::Object);
    val_ori["key"] = std::move(v1);

    Value val_copy(val_ori);
    Value val_assg = val_ori;
    TEST_ASSERT(val_copy.Size() == 1);
    TEST_ASSERT(val_copy == val_assg);
    Value val_move_copy(std::move(val_copy));
    Value val_move_asg = std::move(val_assg);
    TEST_ASSERT(val_copy.IsNull());
    TEST_ASSERT(val_assg.IsNull());
    }

    return true;
}
//---------------------------------------------------------------------------
bool Test_Value_Array()
{
    //array
    Value value_none(Value::Array);
    TEST_ASSERT(value_none.type() == Value::Array);

    Value value(Value::Array);
    TEST_ASSERT(value.type() == Value::Array);
    TEST_ASSERT(0 == value.Size());
    for(auto iter=value.ArrayIterBegin(); value.ArrayIterEnd()!=iter; ++iter)
        assert(0);

    //添加value
    {
    Value v1 = static_cast<unsigned>(1);
    Value v2 = -1;
    Value v3 = 1.0;
    Value v4 = true;
    Value v5 = false; 
    Value v6 = Value(Value::Array);
    Value v7 = Value(Value::Object);
    Value v8 = "string";

    value.ArrayAppend(std::move(v1));
    value.ArrayAppend(std::move(v2));
    value.ArrayAppend(std::move(v3));
    value.ArrayAppend(std::move(v4));
    value.ArrayAppend(std::move(v5));
    value.ArrayAppend(std::move(v6));
    value.ArrayAppend(std::move(v7));
    value.ArrayAppend(std::move(v8));
    }

    size_t size = value.Size();
    TEST_ASSERT(8 == size);

    //检查添加的元素
    {
    const Value& v1 = value[0];
    TEST_ASSERT(v1.AsUInt() == 1);

    const Value& v2 = value[1];
    TEST_ASSERT(v2.AsInt() == -1);

    const Value& v3 = value[2];
    TEST_ASSERT((v3.AsFloat()-1.0)<=0.01);

    const Value& v4 = value[3];
    TEST_ASSERT(v4.AsBoolean() == true);

    const Value& v5 = value[4];
    TEST_ASSERT(v5.AsBoolean() == false);

    const Value& v6 = value[5];
    TEST_ASSERT(v6.IsArray());

    const Value& v7 = value[6];
    TEST_ASSERT(v7.IsObject());

    const Value& v8 = value[7];
    TEST_ASSERT(v8.AsString() == "string");
    }

    for(auto iter=value.ArrayIterBegin(); value.ArrayIterEnd()!=iter; ++iter)
    {
        //FIXME
        //std::cout <<  "value:" << iter->val() << std::endl;
    }

    Value v1_cover = 2;
    value[0] = std::move(v1_cover);
    Value v1_cover_get = value[0];
    TEST_ASSERT(v1_cover_get.AsInt() == 2);

    //删除值
    while(!value.Empty())
    {
        value.ArrayErase(0);
    }
    TEST_ASSERT(value.Empty());

    for(size_t i=0; i<10; i++)
    {
        Value v = i;
        value.ArrayAppend(std::move(v));
    }

    TEST_ASSERT(10 == value.Size());

    for(size_t i=0; i<value.Size(); i++)
    {
        TEST_ASSERT(i == value[static_cast<int>(i)].AsUInt());
    }

    //拷贝构造等等
    {
    Value val(Value::Array);
    Value v1(Value::Array);
    value.ArrayAppend(std::move(v1));

    Value val_copy(val);
    Value val_assg = value;
    TEST_ASSERT(val_assg.Size() == 11);
    Value val_move_copy(std::move(val_copy));
    Value val_move_asg = std::move(val_assg);
    }

    return true;
}
//---------------------------------------------------------------------------
bool Test_Value_Overload()
{
    {
    Value v0 = 10;
    Value v1 = 11;
    TEST_ASSERT(true == (v0 < v1));
    TEST_ASSERT(false == (v0 >= v1));
    TEST_ASSERT(false == (v0 == v1));
    TEST_ASSERT(true == (v0 != v1));
    }

    {
    Value v0 = -10;
    Value v1 = -11;
    TEST_ASSERT(false == (v0 < v1));
    TEST_ASSERT(true == (v0 >= v1));
    TEST_ASSERT(false == (v0 == v1));
    TEST_ASSERT(true == (v0 != v1));
    }

    {
    Value v0 = 10.0f;
    Value v1 = 11.0f;
    TEST_ASSERT(true == (v0 < v1));
    TEST_ASSERT(false == (v0 >= v1));
    TEST_ASSERT(false == (v0 == v1));
    TEST_ASSERT(true == (v0 != v1));
    }

    {
    Value v0 = "string";
    Value v1 = "string1";
    TEST_ASSERT(true == (v0 < v1));
    TEST_ASSERT(false == (v0 >= v1));
    TEST_ASSERT(false == (v0 == v1));
    TEST_ASSERT(true == (v0 != v1));
    }

    {
    Value v0 = true;
    Value v1 = false;
    TEST_ASSERT(false == (v0 < v1));
    TEST_ASSERT(true == (v0 >= v1));
    TEST_ASSERT(false == (v0 == v1));
    TEST_ASSERT(true == (v0 != v1));
    }

    return true;
}
//---------------------------------------------------------------------------
bool Test_Value_ToString()
{
    {
    Value v0 = 1.0;
    std::cout << v0.ToString() << std::endl;

    Value v1 = "string";
    std::cout << v1.ToString() << std::endl;

    Value v2 = 1;
    std::cout << v2.ToString() << std::endl;

    Value v3 = -1;
    std::cout << v3.ToString() << std::endl;

    Value v4 = true;
    std::cout << v4.ToString() << std::endl;

    Value v5 = false;
    std::cout << v5.ToString() << std::endl;

    Value v6;
    std::cout << v6.ToString() << std::endl;
    }

    {
    Value obj(Value::Object);
    obj["k1"] = "string";
    obj["k2"] = 1;
    obj["k3"] = -1;
    obj["k4"] = true;
    obj["k5"] = false;
    obj["k6"] = Value();
    try
    {
        std::cout << obj.ToString() << std::endl;
        TEST_ASSERT(false);
    }
    catch(type_error)
    {}
    }

    {
    Value obj(Value::Array);
    obj.Resize(6);
    obj[0] = Value();
    obj[1] = "string";
    obj[2] = 1;
    obj[3] = -1;
    obj[4] = true;
    obj[5] = false;
    try
    {
        std::cout << obj.ToString() << std::endl;;
    }catch(type_error)
    {}

    }

    {
    Value array(Value::Array);
    array.Resize(2);
    array[0] = "string0";
    array[1] = "string1";

    Value object(Value::Object);
    object["k1"] = 1;
    object["k2"] = 1;
    object["array1"] = std::move(array);
    object["array2"] = array;
    }

    {
    Value array(Value::Array);
    array.Resize(2);

    Value object(Value::Object);
    object["k1"] = 1;
    object["k2"] = 1;
    object["array1"] = Value(Value::Array);
    object["array2"] = Value(Value::Array);
    object["array1"].Resize(2);
    object["array1"][0] = "array1.0";
    object["array1"][1] = "array1.1";
    object["array2"].ArrayAppend(1);
    object["array2"].ArrayAppend(-1);
    object["array2"].ArrayAppend(true);
    object["array2"].ArrayAppend(false);
    object["array2"].ArrayAppend(1.1);
    object["array2"].ArrayAppend("str");

    array[0] = object;
    array[1] = object;
    }

    return true;
}
//---------------------------------------------------------------------------
bool Test_CharReader()
{
    json::CharReader char_reader;
    std::string str = "abcdefghijklmnopqrstuvwxyz";
    char_reader.set_dat(std::string(str));

    int index = 0;
    while(char_reader.HasMore())
    {
        char p = char_reader.Peek();
        char c = char_reader.Next();
        TEST_ASSERT(p == c);
        TEST_ASSERT(str[index++] == c);
    }

    return true;
}
//---------------------------------------------------------------------------
bool Test_TokenReader()
{
    std::string end         = "";
    std::string obj_begin   = "{";
    std::string obj_end     = "}";
    std::string array_begin = "[";
    std::string array_end   = "]";
    std::string colon       = ":";
    std::string comma       = ",";
    std::string t_str       = "\"";
    std::string t_boolean   = "t";
    std::string t_num1      = "-";
    std::string t_num2      = "1";
    std::string t_null      = "n";

    {
    json::TokenReader reader;
    reader.set_dat(std::move(end));
    TEST_ASSERT(json::TokenReader::TokenType::DOCUMENT_END == reader.ReadNextToken());
    }

    {
    json::TokenReader reader;
    reader.set_dat(std::move(obj_begin));
    TEST_ASSERT(json::TokenReader::TokenType::OBJECT_BEGIN == reader.ReadNextToken());
    }

    {
    json::TokenReader reader;
    reader.set_dat(std::move(obj_end));
    TEST_ASSERT(json::TokenReader::TokenType::OBJECT_END == reader.ReadNextToken());
    }

    {
    json::TokenReader reader;
    reader.set_dat(std::move(array_begin));
    TEST_ASSERT(json::TokenReader::TokenType::ARRAY_BEGIN == reader.ReadNextToken());
    }

    {
    json::TokenReader reader;
    reader.set_dat(std::move(array_end));
    TEST_ASSERT(json::TokenReader::TokenType::ARRAY_END == reader.ReadNextToken());
    }

    {
    json::TokenReader reader;
    reader.set_dat(std::move(colon));
    TEST_ASSERT(json::TokenReader::TokenType::SEP_COLON == reader.ReadNextToken());
    }

    {
    json::TokenReader reader;
    reader.set_dat(std::move(comma));
    TEST_ASSERT(json::TokenReader::TokenType::SEP_COMMA == reader.ReadNextToken());
    }

    {
    json::TokenReader reader;
    reader.set_dat(std::move(t_str));
    TEST_ASSERT(json::TokenReader::TokenType::STRING == reader.ReadNextToken());
    }

    {
    json::TokenReader reader;
    reader.set_dat(std::move(t_boolean));
    TEST_ASSERT(json::TokenReader::TokenType::BOOLEAN == reader.ReadNextToken());
    }

    {
    json::TokenReader reader;
    reader.set_dat(std::move(t_num1));
    TEST_ASSERT(json::TokenReader::TokenType::NUMBER == reader.ReadNextToken());
    }

    {
    json::TokenReader reader;
    reader.set_dat(std::move(t_num2));
    TEST_ASSERT(json::TokenReader::TokenType::NUMBER == reader.ReadNextToken());
    }

    {
    json::TokenReader reader;
    reader.set_dat(std::move(t_null));
    TEST_ASSERT(json::TokenReader::TokenType::NUL== reader.ReadNextToken());
    }

    {
    json::TokenReader reader1;
    json::TokenReader reader2;
    json::TokenReader reader3;
    json::TokenReader reader4;
    std::string str         = " normal\"";
    std::string str_spe     = "\\b\\f\\n\\r\\t \\\\ `1~!@#$%^&*()_+-={':[,]}|;.</>? / & \\/ \\\" \"";
    std::string str_err1    = "a";
    std::string str_err3    = "a";
    reader1.set_dat(std::move(str));
    reader2.set_dat(std::move(str_err1));
    reader3.set_dat(std::move(str_spe));
    reader4.set_dat(std::move(str_err3));

    std::string key;
    bool err_code = reader1.ReadString(key);
    TEST_ASSERT(true == err_code);
    TEST_ASSERT(key == " normal");

    key.clear();
    err_code = reader3.ReadString(key);
    TEST_ASSERT(true == err_code);

    err_code = reader2.ReadString(key);
    TEST_ASSERT(false == err_code);

    err_code = reader4.ReadString(key);
    TEST_ASSERT(false == err_code);
    }

    {
    json::TokenReader reader1;
    json::TokenReader reader2;
    json::TokenReader reader3;
    json::TokenReader reader4;
    json::TokenReader reader5;
    std::string n1 = "1234";
    std::string n2 = "-1234";
    std::string n3 = "1234.5678";
    std::string n4 = "a1234";
    std::string n5 = "1a234";
    reader1.set_dat(std::string(n1));
    reader2.set_dat(std::string(n2));
    reader3.set_dat(std::string(n3));
    reader4.set_dat(std::string(n4));
    reader5.set_dat(std::string(n5));

    std::string num;
    json::Value::ValueType num_type;
    bool err_code = reader1.ReadNumber(num, num_type);
    TEST_ASSERT(true == err_code);
    TEST_ASSERT(json::Value::UInt == num_type);
    TEST_ASSERT(n1 == num);
    num.clear();

    err_code = reader2.ReadNumber(num, num_type);
    TEST_ASSERT(true == err_code);
    TEST_ASSERT(json::Value::Int == num_type);
    TEST_ASSERT(n2 == num);
    num.clear();

    err_code = reader3.ReadNumber(num, num_type);
    TEST_ASSERT(true == err_code);
    TEST_ASSERT(json::Value::Real == num_type);
    TEST_ASSERT(n3 == num);
    num.clear();

    err_code = reader4.ReadNumber(num, num_type);
    TEST_ASSERT(false == err_code);
    num.clear();
    }

    {
    json::TokenReader reader1;
    json::TokenReader reader2;
    json::TokenReader reader3;
    json::TokenReader reader4;
    std::string t1 = "true";
    std::string t2 = "false";
    std::string t3 = "taaa";
    std::string t4 = "faaa";
    reader1.set_dat(std::move(t1));
    reader2.set_dat(std::move(t2));
    reader3.set_dat(std::move(t3));
    reader4.set_dat(std::move(t4));

    bool result;
    bool err_code = reader1.ReadBoolean(result);
    TEST_ASSERT(err_code == true);
    TEST_ASSERT(result == true);

    err_code = reader2.ReadBoolean(result);
    TEST_ASSERT(err_code == true);
    TEST_ASSERT(result == false);

    err_code = reader3.ReadBoolean(result);
    TEST_ASSERT(err_code == false);

    err_code = reader4.ReadBoolean(result);
    TEST_ASSERT(err_code == false);
    }

    {
    json::TokenReader reader1;
    json::TokenReader reader2;
    json::TokenReader reader3;
    std::string n1 = "null";
    std::string n2 = "naul";
    std::string n3 = "nul";
    reader1.set_dat(std::move(n1));
    reader2.set_dat(std::move(n2));
    reader3.set_dat(std::move(n3));

    bool err_code= reader1.ReadNull();
    TEST_ASSERT(true == err_code);

    err_code= reader2.ReadNull();
    TEST_ASSERT(false == err_code);

    err_code= reader3.ReadNull();
    TEST_ASSERT(false == err_code);
    }

    return true;
}
//---------------------------------------------------------------------------
bool Test_Json_KV()
{
    //null kv
    {
    json::JsonReader reader;
    std::string str = "{}";

    std::string j_str;
    json::Value root;
    bool err_code = reader.Parse(str, root);
    TEST_ASSERT(true == err_code);

    j_str = json::JsonWriter(root).ToString();
    assert(j_str == str);
    }

    //string
    {
    json::JsonReader reader;
    std::string str = "{\"key1\":\"value1\",\"key2\":\"value2\",\"key3\":\"value3\"}";

    std::string j_str;
    json::Value root;
    bool err_code = reader.Parse(str, root);
    TEST_ASSERT(true == err_code);

    j_str = json::JsonWriter(root).ToString();
    assert(j_str == str);
    }

    //number
    {
    json::JsonReader reader;
    std::string str = "{\"key1\":-1,\"key2\":123,\"key3\":1245.567800}";

    json::Value root;
    bool err_code = reader.Parse(str, root);
    TEST_ASSERT(true == err_code);

    std::string j_str = json::JsonWriter(root).ToString();
    assert(j_str == str);
    }

    //boolean
    {
    json::JsonReader reader;
    std::string str = "{\"key1\":true,\"key2\":false}";

    json::Value root;
    bool err_code = reader.Parse(str, root);
    TEST_ASSERT(true == err_code);

    std::string j_str = json::JsonWriter(root).ToString();
    assert(j_str == str);
    }

    //null
    {
    json::JsonReader reader;
    std::string str = "{\"key1\":null}";

    json::Value root;
    bool err_code = reader.Parse(str, root);
    TEST_ASSERT(true == err_code);

    std::string j_str = json::JsonWriter(root).ToString();
    assert(j_str == str);
    }

    return true;
}
//---------------------------------------------------------------------------
bool Test_Json_Array()
{
    //nll
    {
    json::JsonReader reader;
    std::string str = "[]";

    json::Value root;
    bool err_code = reader.Parse(str, root);
    TEST_ASSERT(true == err_code);

    std::string j_str = json::JsonWriter(root).ToString();
    assert(j_str == str);
    }

    //杂七杂八
    {
    json::JsonReader reader;
    std::string str = "[1,\"value2\",null,true,false,1.100000,-1]";

    json::Value root;
    bool err_code = reader.Parse(str, root);
    TEST_ASSERT(true == err_code);

    std::string j_str = json::JsonWriter(root).ToString();
    assert(j_str == str);

    }

    //string
    {
    json::JsonReader reader;
    std::string str = "{\"key\":[\"value1\",\"value2\"]}";

    json::Value root;
    bool err_code = reader.Parse(str, root);
    TEST_ASSERT(true == err_code);

    std::string j_str = json::JsonWriter(root).ToString();
    assert(j_str == str);
    }

    //number
    {
    json::JsonReader reader;
    std::string str = "{\"key\":[1,-1,1234.567800]}";

    json::Value root;
    bool err_code = reader.Parse(str, root);
    TEST_ASSERT(true == err_code);

    std::string j_str = json::JsonWriter(root).ToString();
    assert(j_str == str);
    }

    //boolean
    {
    json::JsonReader reader;
    std::string str = "{\"key\":[true,false]}";

    json::Value root;
    bool err_code = reader.Parse(str, root);
    TEST_ASSERT(true == err_code);

    std::string j_str = json::JsonWriter(root).ToString();
    assert(j_str == str);
    }

    //null
    {
    json::JsonReader reader;
    std::string str = "{\"key\":[null,null,null]}";

    json::Value root;
    bool err_code = reader.Parse(str, root);
    TEST_ASSERT(true == err_code);

    std::string j_str = json::JsonWriter(root).ToString();
    assert(j_str == str);
    }

    return true;
}
//---------------------------------------------------------------------------
bool Test_Json_Object()
{
    //string
    {
    json::JsonReader reader;
    std::string str = "{\"key\":{\"objkey1\":\"obj_value1\",\"objkey2\":\"obj_value2\"}}";

    json::Value root;
    bool err_code = reader.Parse(str, root);
    TEST_ASSERT(true == err_code);

    std::string j_str = json::JsonWriter(root).ToString();
    assert(j_str == str);
    }

    //nmber
    {
    json::JsonReader reader;
    std::string str = "{\"key\":{\"objkey1\":1,\"objkey2\":-1,\"objkey3\":1234.567800}}";

    json::Value root;
    bool err_code = reader.Parse(str, root);
    TEST_ASSERT(true == err_code);

    std::string j_str = json::JsonWriter(root).ToString();
    assert(j_str == str);
    }

    //boolean
    {
    json::JsonReader reader;
    std::string str = "{\"key\":{\"objkey1\":true,\"objkey2\":false}}";

    json::Value root;
    bool err_code = reader.Parse(str, root);
    TEST_ASSERT(true == err_code);

    std::string j_str = json::JsonWriter(root).ToString();
    assert(j_str == str);
    }

    //null
    {
    json::JsonReader reader;
    std::string str = "{\"key\":{\"objkey1\":null,\"objkey2\":null}}";

    json::Value root;
    bool err_code = reader.Parse(str, root);
    TEST_ASSERT(true == err_code);

    std::string j_str = json::JsonWriter(root).ToString();
    assert(j_str == str);
    }

    return true;
}
//---------------------------------------------------------------------------
bool Test_Json_File()
{
    //测试一个文件夹下的数据

    const char* test_dir = "../../test/json_file/";
    DIR* dir = opendir(test_dir);
    if(0 == dir)
        TEST_ASSERT(0);

    std::list<std::string> pass_file_list;
    std::list<std::string> fail_file_list;
    for(struct dirent* ent=readdir(dir); 0!=ent; ent=readdir(dir))
    {
        if(DT_REG & ent->d_type)
        {
            if('f' == ent->d_name[0])
                fail_file_list.push_back(ent->d_name);
            else if('p' == ent->d_name[0])
                pass_file_list.push_back(ent->d_name);
        }
    }
    closedir(dir);

    //错误的文件
    for(auto i=fail_file_list.begin(); i!=fail_file_list.end(); ++i)
    {
        json::Value root;
        json::JsonReader reader;
        std::string path = test_dir + *i;
        bool err_code = reader.ParseFile(path, root);
        TEST_ASSERT(false == err_code);
    }

    //正确的文件
    for(auto i=pass_file_list.begin(); i!=pass_file_list.end(); ++i)
    {
        json::Value root;
        json::JsonReader reader;
        std::string path = test_dir + *i;
        bool err_code = reader.ParseFile(path, root);
        TEST_ASSERT(true == err_code);

        std::string str = json::JsonWriter(root).ToString(true);
        std::string save_file = *i;
        JsonWriter w(root);
        TEST_ASSERT(w.ToFile(save_file, true))
    }

    return true;
}
//---------------------------------------------------------------------------
bool Test_json_Format()
{
    const char* test_dir = "../../test/json_file/tostring.json";
    std::string file = test_dir;
    json::Value root;
    json::JsonReader reader;
    bool err_code = reader.ParseFile(file, root);
    if(false == err_code)
        return false;

    std::string format_str = json::JsonWriter(root).ToString(true);
    std::cout << format_str << std::endl;
    return true;
}
//---------------------------------------------------------------------------
int main(int, char**)
{
    TestTitle();

    Test_Value_Base();
    Test_Value_Obj();
    Test_Value_Array();
    Test_Value_Overload();
    Test_Value_ToString();
    Test_CharReader();
    Test_TokenReader();
    Test_Json_KV();
    Test_Json_Array();
    Test_Json_Object();
    Test_Json_File();
    Test_json_Format();

    return 0;
}
