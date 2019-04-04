//---------------------------------------------------------------------------
#include "test_inc.h"
#include "../src/json/token_reader.h"
#include "../src/json/char_reader.h"
#include "../src/json/json_reader.h"
#include "../src/json/value.h"
#include "../src/json/json_writer.h"
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
    Value value_none(Value::Key);
    const char* c_str = "key";
    value_none.set_str(c_str);
    TEST_ASSERT(value_none.AsString() == std::string(c_str));

    std::string s_str = "key";
    value_none.set_str(s_str);
    TEST_ASSERT(value_none.AsString() == s_str);
    value_none.set_str(std::move(s_str));
    TEST_ASSERT(value_none.AsString() == std::string(c_str));

    Value value(Value::Key);
    TEST_ASSERT(Value::Key == value.type());
    value.set_str(c_str);
    TEST_ASSERT(value.AsString() == std::string(c_str));

    std::string str = "key";
    value.set_str(str);
    TEST_ASSERT(value.AsString() == str);
    value.set_str(std::move(str));
    TEST_ASSERT(value.AsString() == std::string(c_str));

    //复制构造
    Value val_copy(value);
    TEST_ASSERT(value.AsString() == val_copy.AsString());

    //=
    Value val_assg = value;
    TEST_ASSERT(value.AsString() == val_assg.AsString());

    //move
    Value val_move(std::move(val_copy));
    TEST_ASSERT(value.AsString() == val_move.AsString());

    //move==
    Value val_move_assg = std::move(val_assg);
    TEST_ASSERT(value.AsString() == val_move_assg.AsString());
    }

    /*
    //string
    {
    //基本操作
    Value value_none(Value::STRING);
    const char* c_str = "string";
    value_none.set_str(c_str);
    TEST_ASSERT(value_none.val() == std::string(c_str));

    std::string s_str = "string";
    value_none.set_str(s_str);
    TEST_ASSERT(value_none.val() == s_str);
    value_none.set_str(std::move(s_str));
    TEST_ASSERT(value_none.val() == std::string(c_str));

    Value value(Value::STRING);
    TEST_ASSERT(Value::STRING == value.type());
    value.set_str(c_str);
    TEST_ASSERT(value.val() == std::string(c_str));

    std::string str = "string";
    value.set_str(str);
    TEST_ASSERT(value.val() == str);
    value.set_str(std::move(str));
    TEST_ASSERT(value.val() == std::string(c_str));

    //复制构造
    Value val_copy(value);
    TEST_ASSERT(value.val() == val_copy.val());

    //=
    Value val_assg= value;
    TEST_ASSERT(value.val() == val_assg.val());

    //move
    Value val_move(std::move(val_copy));
    TEST_ASSERT(value.val() == val_move.val());

    //move==
    Value val_move_assg = std::move(val_assg);
    TEST_ASSERT(value.val() == val_move_assg.val());
    }

    //int
    {
    //基本操作
    Value value_none(Value::INT);
    int64_t int64 = 0x7FFFFFFFFFFFFFFF;
    value_none.set_int(int64);
    TEST_ASSERT(value_none.val() == base::CombineString("%" PRId64 "", int64));
    TEST_ASSERT(value_none.get_int() == int64);

    Value value(Value::INT);
    TEST_ASSERT(Value::INT == value.type());
    value.set_int(int64);
    TEST_ASSERT(value.val() == base::CombineString("%" PRId64 "", int64));
    TEST_ASSERT(value.get_int() == int64);

    //复制构造
    Value val_copy(value);
    TEST_ASSERT(value.val() == val_copy.val());

    //=
    Value val_assg= value;
    TEST_ASSERT(value.val() == val_assg.val());

    //move
    Value val_move(std::move(val_copy));
    TEST_ASSERT(value.val() == val_move.val());

    //move==
    Value val_move_assg = std::move(val_assg);
    TEST_ASSERT(value.val() == val_move_assg.val());
    }

    //uint
    {
    //基本操作
    Value value_none(Value::UINT);
    uint64_t uint64 = 0xFFFFFFFFFFFFFFFF;
    value_none.set_uint(uint64);
    TEST_ASSERT(value_none.val() == base::CombineString("%" PRIu64 "", uint64));
    TEST_ASSERT(value_none.get_uint() == uint64);

    Value value(Value::UINT);
    TEST_ASSERT(Value::UINT == value.type());
    value.set_uint(uint64);
    TEST_ASSERT(value.val() == base::CombineString("%" PRIu64 "", uint64));
    TEST_ASSERT(value.get_uint() == uint64);

    //复制构造
    Value val_copy(value);
    TEST_ASSERT(value.val() == val_copy.val());

    //=
    Value val_assg= value;
    TEST_ASSERT(value.val() == val_assg.val());

    //move
    Value val_move(std::move(val_copy));
    TEST_ASSERT(value.val() == val_move.val());

    //move==
    Value val_move_assg = std::move(val_assg);
    TEST_ASSERT(value.val() == val_move_assg.val());
    }

    //real
    {
    //基本操作
    Value value_none(Value::REAL);
    double real = 1.7E+100;
    value_none.set_double(real);
    double real1 = value_none.get_double();
    TEST_ASSERT(0 == (real - real1));
    TEST_ASSERT(value_none.get_double() == real);

    Value value(Value::REAL);
    TEST_ASSERT(Value::REAL == value.type());
    value.set_double(real);
    TEST_ASSERT(value.get_double() == real);

    //复制构造
    Value val_copy(value);
    TEST_ASSERT(value.val() == val_copy.val());

    //=
    Value val_assg= value;
    TEST_ASSERT(value.val() == val_assg.val());

    //move
    Value val_move(std::move(val_copy));
    TEST_ASSERT(value.val() == val_move.val());

    //move==
    Value val_move_assg = std::move(val_assg);
    TEST_ASSERT(value.val() == val_move_assg.val());
    }

    //boolean true
    {
    //基本操作
    Value value_none(Value::BOOLEAN);
    bool boolean = true;
    value_none.set_boolean(boolean);
    TEST_ASSERT(value_none.val() == "true");
    TEST_ASSERT(value_none.get_boolean() == boolean);

    Value value(Value::BOOLEAN);
    TEST_ASSERT(Value::BOOLEAN == value.type());
    value.set_boolean(boolean);
    TEST_ASSERT(value.val() == "true");
    TEST_ASSERT(value.get_boolean() == boolean);

    //复制构造
    Value val_copy(value);
    TEST_ASSERT(value.val() == val_copy.val());

    //=
    Value val_assg= value;
    TEST_ASSERT(value.val() == val_assg.val());

    //move
    Value val_move(std::move(val_copy));
    TEST_ASSERT(value.val() == val_move.val());

    //move==
    Value val_move_assg = std::move(val_assg);
    TEST_ASSERT(value.val() == val_move_assg.val());
    }

    //boolean false
    {
    //基本操作
    Value value_none(Value::BOOLEAN);
    bool boolean = false;
    value_none.set_boolean(boolean);
    TEST_ASSERT(value_none.val() == "false");
    TEST_ASSERT(value_none.get_boolean() == boolean);

    Value value(Value::BOOLEAN);
    TEST_ASSERT(Value::BOOLEAN == value.type());
    value.set_boolean(boolean);
    TEST_ASSERT(value.val() == "false");
    TEST_ASSERT(value.get_boolean() == boolean);

    //复制构造
    Value val_copy(value);
    TEST_ASSERT(value.val() == val_copy.val());

    //=
    Value val_assg= value;
    TEST_ASSERT(value.val() == val_assg.val());

    //move
    Value val_move(std::move(val_copy));
    TEST_ASSERT(value.val() == val_move.val());

    //move==
    Value val_move_assg = std::move(val_assg);
    TEST_ASSERT(value.val() == val_move_assg.val());
    }

    //null
    {
    //基本操作
    Value value_none(Value::NUL);
    TEST_ASSERT(value_none.val() == "null");

    Value value(Value::NUL);
    TEST_ASSERT(value.val() == "null");

    //复制构造
    Value val_copy(value);
    TEST_ASSERT(value.val() == val_copy.val());

    //=
    Value val_assg= value;
    TEST_ASSERT(value.val() == val_assg.val());

    //move
    Value val_move(std::move(val_copy));
    TEST_ASSERT(value.val() == val_move.val());

    //move==
    Value val_move_assg = std::move(val_assg);
    TEST_ASSERT(value.val() == val_move_assg.val());
    }

    //初始即构造
    {
    std::string v_str = "str";
    Value v_str1("str");
    Value v_str2(std::string("str"));
    Value v_str3(std::move(v_str));
    TEST_ASSERT(Value::STRING == v_str1.type());
    TEST_ASSERT(Value::STRING == v_str2.type());
    TEST_ASSERT(Value::STRING == v_str3.type());
    TEST_ASSERT("str" == v_str1.val());
    TEST_ASSERT("str" == v_str2.val());
    TEST_ASSERT("str" == v_str3.val());

    int64_t int64 = 1;
    Value v_int(int64);
    TEST_ASSERT(Value::INT == v_int.type());
    TEST_ASSERT(1 == v_int.get_int());

    uint64_t uint64 = 1;
    Value v_uint(uint64);
    TEST_ASSERT(Value::UINT == v_uint.type());
    TEST_ASSERT(1 == v_uint.get_uint());

    bool boolean = true;
    Value v_boolean(boolean);
    TEST_ASSERT(Value::BOOLEAN == v_boolean.type());
    TEST_ASSERT(true == v_boolean.get_boolean());

    double real = 1;
    Value v_real(real);
    TEST_ASSERT(Value::REAL == v_real.type());

    }

    {
        Value valuen;
        Value values("aaa");
        valuen = Value(Value::OBJECT);
        valuen = Value(Value::ARRAY);
        values = Value(Value::OBJECT);
        values = Value(Value::ARRAY);
    }
    */

    return true;
}
//---------------------------------------------------------------------------
/*
bool Test_Value_Obj()
{
    //object
    Value value_none(Value::OBJECT);
    TEST_ASSERT(value_none.type() == Value::OBJECT);
    TEST_ASSERT(value_none.val() == "null");

    Value value(Value::OBJECT);
    TEST_ASSERT(value.type() == Value::OBJECT);
    TEST_ASSERT(value.val() == "null");

    //初始状态
    TEST_ASSERT(0 == value.PairSize());
    TEST_ASSERT(false == value.PairDel("none"));
    TEST_ASSERT(false == value.PairDel(std::string("none")));

    Value v;
    TEST_ASSERT(false == value.PairGet("none", &v));
    TEST_ASSERT(false == value.PairGet(std::string("none"), &v));
    size_t count = 0;
    for(auto iter=value.PairIterBegin(); value.PairIterEnd()!=iter; ++iter)
        count ++;
    TEST_ASSERT(0 == count);

    //添加pair
    {
    Value v1(Value::INT);
    v1.set_int(-1);
    Value v2(Value::UINT);
    v2.set_uint(1);
    Value v3(Value::REAL);
    v3.set_double(1.1);
    Value v4(Value::BOOLEAN);
    v4.set_boolean(true);
    Value v5(Value::BOOLEAN);
    v5.set_boolean(false);
    Value v6(Value::NUL);

    value.PairAdd("key1", std::move(v1));
    value.PairAdd(std::string("key2"), std::move(v2));
    std::string key3 = "key3";
    value.PairAdd(std::move(key3), std::move(v3));
    value.PairAdd("key4", std::move(v4));
    value.PairAdd(std::string("key5"), std::move(v5));
    std::string key6 = "key6";
    value.PairAdd(std::move(key6), std::move(v6));
    }

    size_t size = value.PairSize();
    TEST_ASSERT(6 == size);

    //检查添加的元素
    {
    Value v1;
    TEST_ASSERT(true == value.PairGet("key1", &v1));
    TEST_ASSERT(v1.get_int() == -1);

    Value v2;
    TEST_ASSERT(true == value.PairGet(std::string("key2"), &v2));
    TEST_ASSERT(v2.get_uint() == 1);

    Value v3;
    TEST_ASSERT(true == value.PairGet("key3", &v3));
    TEST_ASSERT((v3.get_double() - 1.1)<0.01);

    Value v4;
    TEST_ASSERT(true == value.PairGet("key4", &v4));
    TEST_ASSERT(v4.get_boolean() == true);

    Value v5;
    TEST_ASSERT(true == value.PairGet("key5", &v5));
    TEST_ASSERT(v5.get_boolean() == false);

    Value v6;
    TEST_ASSERT(true == value.PairGet("key6", &v6));
    TEST_ASSERT(v6.type() == Value::NUL);

    for(auto iter=value.PairIterBegin(); value.PairIterEnd()!=iter; ++iter)
    {
        std::cout << "key:" << iter->first << " value:" << iter->second.val() << std::endl;
    }

    //添加同样key值的会被覆盖
    Value v1_cover(Value::INT);
    v1_cover.set_int(2);
    value.PairAdd("key1", std::move(v1_cover));
    Value v1_cover_get;
    TEST_ASSERT(true ==  value.PairGet("key1", &v1_cover_get));
    TEST_ASSERT(v1_cover_get.get_int()==2);

    //删除key值
    TEST_ASSERT(value.PairDel("key1"));
    TEST_ASSERT(value.PairDel("key2"));
    TEST_ASSERT(value.PairDel("key3"));
    TEST_ASSERT(value.PairDel("key4"));
    TEST_ASSERT(value.PairDel("key5"));
    TEST_ASSERT(value.PairDel("key6"));

    TEST_ASSERT(0 == value.PairSize());
    for(auto iter=value.PairIterBegin(); value.PairIterEnd()!=iter; ++iter)
    {
        //没有元素
        assert(0);
    }
    }

    //拷贝构造等等
    {
    Value val(Value::OBJECT);
    Value v1(Value::OBJECT);
    value.PairAdd("key", std::move(v1));

    Value val_copy(val);
    Value val_assg = value;
    Value val_move_copy(std::move(val_copy));
    Value val_move_asg = std::move(val_assg);
    }

    return true;
}
//---------------------------------------------------------------------------
bool Test_Value_Array()
{
    //array
    Value value_none(Value::ARRAY);
    TEST_ASSERT(value_none.type() == Value::ARRAY);
    TEST_ASSERT(value_none.val() == "null");

    Value value(Value::ARRAY);
    TEST_ASSERT(value.type() == Value::ARRAY);
    TEST_ASSERT(value.val() == "null");

    //初始状态
    TEST_ASSERT(0 == value.ArraySize());
    for(auto iter=value.ArrayIterBegin(); value.ArrayIterEnd()!=iter; ++iter)
        assert(0);

    //添加value
    {
    Value v1(Value::INT);
    v1.set_int(-1);
    Value v2(Value::UINT);
    v2.set_uint(1);
    Value v3(Value::REAL);
    v3.set_double(1.1);
    Value v4(Value::BOOLEAN);
    v4.set_boolean(true);
    Value v5(Value::BOOLEAN);
    v5.set_boolean(false);
    Value v6(Value::NUL);

    value.ArrayAdd(std::move(v1));
    value.ArrayAdd(std::move(v2));
    value.ArrayAdd(std::move(v3));
    value.ArrayAdd(std::move(v4));
    value.ArrayAdd(std::move(v5));
    value.ArrayAdd(std::move(v6));
    }

    size_t size = value.ArraySize();
    TEST_ASSERT(6 == size);

    //检查添加的元素
    {
    Value v1 = value.ArrayGet(0);
    TEST_ASSERT(v1.get_int() == -1);

    Value v2 = value.ArrayGet(1);
    TEST_ASSERT(v2.get_uint() == 1);

    Value v3 = value.ArrayGet(2);
    TEST_ASSERT((v3.get_double() - 1.1)<0.01);

    Value v4 = value.ArrayGet(3);
    TEST_ASSERT(v4.get_boolean() == true);

    Value v5 = value.ArrayGet(4);
    TEST_ASSERT(v5.get_boolean() == false);

    Value v6 = value.ArrayGet(5);
    TEST_ASSERT(v6.type() == Value::NUL);
    }

    for(auto iter=value.ArrayIterBegin(); value.ArrayIterEnd()!=iter; ++iter)
    {
        std::cout <<  "value:" << iter->val() << std::endl;
    }

    //添加同样key值的会被覆盖
    Value v1_cover(Value::INT);
    v1_cover.set_int(2);
    value.ArraySet(0, std::move(v1_cover));
    Value v1_cover_get = value.ArrayGet(0);
    TEST_ASSERT(v1_cover_get.get_int()==2);

    //删除值
    for(size_t i=0; i<value.ArraySize(); i++)
    {
        value.ArrayZero(i);
        TEST_ASSERT(value.ArrayGet(i).val() == "null");
    }

    //重置大小
    value.ArrayResize(0);
    value.ArrayResize(10);

    for(size_t i=0; i<10; i++)
    {
        Value v(Value::INT);
        v.set_int(i);
        value.ArraySet(i, std::move(v));
    }

    TEST_ASSERT(10 == value.ArraySize());

    for(size_t i=0; i<value.ArraySize(); i++)
    {
        TEST_ASSERT(static_cast<int64_t>(i) == value.ArrayGet(i).get_int());
    }

    //拷贝构造等等
    {
    Value val(Value::ARRAY);
    Value v1(Value::ARRAY);
    value.ArrayAdd(std::move(v1));

    Value val_copy(val);
    Value val_assg = value;
    Value val_move_copy(std::move(val_copy));
    Value val_move_asg = std::move(val_assg);
    }

    return true;
}
//---------------------------------------------------------------------------
bool Test_Value_Overload()
{
    {
    Value v1 = "string";
    std::cout << v1.ToString(true) << std::endl;
    std::cout << v1.ToString() << std::endl;

    Value v2 = 1;
    std::cout << v2.ToString(true) << std::endl;
    std::cout << v2.ToString() << std::endl;

    Value v3 = -1;
    std::cout << v3.ToString(true) << std::endl;
    std::cout << v3.ToString() << std::endl;

    Value v4 = true;
    std::cout << v4.ToString(true) << std::endl;
    std::cout << v4.ToString() << std::endl;

    Value v5 = false;
    std::cout << v5.ToString(true) << std::endl;
    std::cout << v5.ToString() << std::endl;

    Value v6;
    std::cout << v6.ToString(true) << std::endl;
    std::cout << v6.ToString() << std::endl;
    }

    {
    std::cout << "object :" << std::endl;
    Value obj(Value::OBJECT);
    obj["k1"] = "string";
    obj["k2"] = 1;
    obj["k3"] = -1;
    obj["k4"] = true;
    obj["k5"] = false;
    obj["k6"] = Value();
    std::cout << obj.ToString(true) << std::endl;
    std::cout << obj.ToString() << std::endl;
    }

    {
    std::cout << "array:" << std::endl;
    Value obj(Value::ARRAY);
    obj.ArrayResize(6);
    obj[0] = Value();
    obj[1] = "string";
    obj[2] = 1;
    obj[3] = -1;
    obj[4] = true;
    obj[5] = false;
    std::cout << obj.ToString(true) << std::endl;
    std::cout << obj.ToString() << std::endl;;
    }

    {
    std::cout << "object array:" << std::endl;

    Value array(Value::ARRAY);
    array.ArrayResize(2);
    array[0] = "string0";
    array[1] = "string1";

    Value object(Value::OBJECT);
    object["k1"] = 1;
    object["k2"] = 1;
    object["array1"] = std::move(array);
    object["array2"] = array;

    std::cout << object.ToString() << std::endl;
    std::cout << object.ToString(true) << std::endl;
    }

    {
    std::cout << "object array:" << std::endl;

    Value array(Value::ARRAY);
    array.ArrayResize(2);

    Value object(Value::OBJECT);
    object["k1"] = 1;
    object["k2"] = 1;
    object["array1"] = Value(Value::ARRAY);
    object["array2"] = Value(Value::ARRAY);
    object["array1"].ArrayResize(2);
    object["array1"][0] = "array1.0";
    object["array1"][1] = "array1.1";
    object["array2"].ArrayAdd(1);
    object["array2"].ArrayAdd(-1);
    object["array2"].ArrayAdd(true);
    object["array2"].ArrayAdd(false);
    object["array2"].ArrayAdd(1.1);
    object["array2"].ArrayAdd("str");

    array[0] = object;
    array[1] = object;
    std::cout << array.ToString() << std::endl;
    std::cout << array.ToString(true) << std::endl;
    }

    return true;
}
//---------------------------------------------------------------------------
bool Test_CharReader()
{
    json::CharReader char_reader;
    std::string str = "abcdefghijklmnopqrstuvwxyz";
    char_reader.set_dat(std::move(str));

    for(char c=char_reader.Peek(); true==char_reader.HasMore(); c=char_reader.Next())
    {
        printf("%c\n", c);
    }

    return true;
}
//---------------------------------------------------------------------------
bool Test_TokenReader()
{
    enum
    {
        T_DOCUMENT_END = 1,   // 分析结束
        T_OBJECT_BEGIN,       // obj开始
        T_OBJECT_END,         // obj结束
        T_ARRAY_BEGIN,        // array开始
        T_ARRAY_END,          // array结束
        T_SEP_COLON,          // 分隔符 :
        T_SEP_COMMA,          // 分隔符 ,
        T_STRING,             // 字符串
        T_BOOLEAN,            // 布尔值
        T_NUMBER,             // 数值
        T_NUL,                // 空
        T_INVALID             // 非法的字符
    };
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
    std::cout << "---" << std::endl;
    std::cout << key <<std::endl;
    std::cout << "---" << std::endl;
    //TEST_ASSERT(key == str_spe);

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
    json::Value::TYPE num_type;
    bool err_code = reader1.ReadNumber(num, num_type);
    TEST_ASSERT(true == err_code);
    TEST_ASSERT(json::Value::UINT == num_type);
    TEST_ASSERT(n1 == num);
    num.clear();

    err_code = reader2.ReadNumber(num, num_type);
    TEST_ASSERT(true == err_code);
    TEST_ASSERT(json::Value::INT == num_type);
    TEST_ASSERT(n2 == num);
    num.clear();

    err_code = reader3.ReadNumber(num, num_type);
    TEST_ASSERT(true == err_code);
    TEST_ASSERT(json::Value::REAL == num_type);
    TEST_ASSERT(n3 == num);
    num.clear();

    err_code = reader4.ReadNumber(num, num_type);
    TEST_ASSERT(false == err_code);
    num.clear();

    // err_code = reader5.ReadNumber(num);
    //TEST_ASSERT(false == err_code);
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
    bool err_code = reader.Parse(str, &root);
    TEST_ASSERT(true == err_code);

    j_str = json::JsonWriter(root).ToString();
    assert(j_str == str);
    }

    //string
    {
    json::JsonReader reader;
    std::string str = "{\"key1\":\"value2\",\"key2\":\"value2\",\"key3\":\"value3\"}";

    std::string j_str;
    json::Value root;
    bool err_code = reader.Parse(str, &root);
    TEST_ASSERT(true == err_code);

    j_str = json::JsonWriter(root).ToString();
    assert(j_str == str);
    }

    //number
    {
    json::JsonReader reader;
    std::string str = "{\"key1\":-1,\"key2\":123,\"key3\":1245.5678}";

    json::Value root;
    bool err_code = reader.Parse(str, &root);
    TEST_ASSERT(true == err_code);

    std::string j_str = json::JsonWriter(root).ToString();
    assert(j_str == str);
    }

    //boolean
    {
    json::JsonReader reader;
    std::string str = "{\"key1\":true,\"key2\":false}";

    json::Value root;
    bool err_code = reader.Parse(str, &root);
    TEST_ASSERT(true == err_code);

    std::string j_str = json::JsonWriter(root).ToString();
    assert(j_str == str);
    }

    //null
    {
    json::JsonReader reader;
    std::string str = "{\"key1\":null}";

    json::Value root;
    bool err_code = reader.Parse(str, &root);
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
    bool err_code = reader.Parse(str, &root);
    TEST_ASSERT(true == err_code);

    std::string j_str = json::JsonWriter(root).ToString();
    assert(j_str == str);
    }

    //杂七杂八
    {
    json::JsonReader reader;
    std::string str = "[1,\"value2\",null,true,false,1.1,-1]";

    json::Value root;
    bool err_code = reader.Parse(str, &root);
    TEST_ASSERT(true == err_code);

    std::string j_str = json::JsonWriter(root).ToString();
    assert(j_str == str);

    }

    //string
    {
    json::JsonReader reader;
    std::string str = "{\"key\":[\"value1\",\"value2\"]}";

    json::Value root;
    bool err_code = reader.Parse(str, &root);
    TEST_ASSERT(true == err_code);

    std::string j_str = json::JsonWriter(root).ToString();
    assert(j_str == str);
    }

    //number
    {
    json::JsonReader reader;
    std::string str = "{\"key\":[1,-1,1234.5678]}";

    json::Value root;
    bool err_code = reader.Parse(str, &root);
    TEST_ASSERT(true == err_code);

    std::string j_str = json::JsonWriter(root).ToString();
    assert(j_str == str);
    }

    //boolean
    {
    json::JsonReader reader;
    std::string str = "{\"key\":[true,false]}";

    json::Value root;
    bool err_code = reader.Parse(str, &root);
    TEST_ASSERT(true == err_code);

    std::string j_str = json::JsonWriter(root).ToString();
    assert(j_str == str);
    }

    //null
    {
    json::JsonReader reader;
    std::string str = "{\"key\":[null,null,null]}";

    json::Value root;
    bool err_code = reader.Parse(str, &root);
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
    bool err_code = reader.Parse(str, &root);
    TEST_ASSERT(true == err_code);

    std::string j_str = json::JsonWriter(root).ToString();
    assert(j_str == str);
    }

    //nmber
    {
    json::JsonReader reader;
    std::string str = "{\"key\":{\"objkey1\":1,\"objkey2\":-1,\"objkey3\":1234.5678}}";

    json::Value root;
    bool err_code = reader.Parse(str, &root);
    TEST_ASSERT(true == err_code);

    std::string j_str = json::JsonWriter(root).ToString();
    assert(j_str == str);
    }

    //boolean
    {
    json::JsonReader reader;
    std::string str = "{\"key\":{\"objkey1\":true,\"objkey2\":false}}";

    json::Value root;
    bool err_code = reader.Parse(str, &root);
    TEST_ASSERT(true == err_code);

    std::string j_str = json::JsonWriter(root).ToString();
    assert(j_str == str);
    }

    //null
    {
    json::JsonReader reader;
    std::string str = "{\"key\":{\"objkey1\":null,\"objkey2\":null}}";

    json::Value root;
    bool err_code = reader.Parse(str, &root);
    TEST_ASSERT(true == err_code);

    std::string j_str = json::JsonWriter(root).ToString();
    assert(j_str == str);
    }

    return true;
}
//---------------------------------------------------------------------------
bool Test_Json_ArrayObject()
{
    //测试一个文件夹下的数据

    const char* test_dir = "../../test/json_file/";
    DIR* dir = opendir(test_dir);
    if(0 == dir)
        return false;

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
        json::Value         root;
        json::JsonReader    reader;
        std::string path = test_dir + *i;
        bool err_code = reader.ParseFile(path, &root);
        TEST_ASSERT(false == err_code);
        std::cout << "test fail file:" << path << " sucess" << std::endl;
    }

    //正确的文件
    for(auto i=pass_file_list.begin(); i!=pass_file_list.end(); ++i)
    {
        json::Value         root;
        json::JsonReader    reader;
        std::string path = test_dir + *i;
        bool err_code = reader.ParseFile(path, &root);
        TEST_ASSERT(true == err_code);

        std::string str = json::JsonWriter(root).ToString(true);
        std::string save_file = *i;
        JsonWriter w(root);
        if(false == w.ToFile(save_file, true))
            return false;
        std::cout << "test success file:" << path << " sucess" << std::endl;
    }

    return true;
}
//---------------------------------------------------------------------------
bool Test_json_Format()
{
    const char* test_dir = "../../test/json_file/tostring.json";
    std::string         file    =  test_dir;
    json::Value         root;
    json::JsonReader    reader;
    bool err_code = reader.ParseFile(file, &root);
    if(false == err_code)
        return false;

    std::string format_str = json::JsonWriter(root).ToString(true);
    std::cout << format_str << std::endl;
    return true;
}
*/
//---------------------------------------------------------------------------
int main(int, char**)
{
    TestTitle();

    Test_Value_Base();
  //  Test_Value_Obj();
  //  Test_Value_Array();
  //  Test_Value_Overload();
  //  Test_CharReader();
  //  Test_TokenReader();
  //  Test_Json_KV();
  //  Test_Json_Array();
  //  Test_Json_Object();
  //  Test_Json_ArrayObject();
  //  Test_json_Format();

    return 0;
}
