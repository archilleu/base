//---------------------------------------------------------------------------
#include "test_inc.h"
#include "../src/function.h"
#include "../src/memory_block.h"
//---------------------------------------------------------------------------
using namespace base;
using namespace base::test;
//---------------------------------------------------------------------------
bool Test_String()
{
    int32_t int32 = (static_cast<uint32_t>(-1)) >> 1;
    uint32_t uint32 = static_cast<uint32_t>(-1);
    int64_t int64 = (static_cast<uint64_t>(-1)) >> 1;
    uint64_t uint64 = static_cast<uint64_t>(-1);
    const char* str = "haha";
    int* ptr = &int32;
    size_t size_t1 = -100;

    const char* format = "int32_t:%ld, uint32_t:%lu, int64_t:%lld, uint64_t:%llu, char:%s, point:%p, size_t:%zu";
    std::string target = CombineString(format, int32, uint32, int64, uint64, str, ptr, size_t1);

    char standard[1024];
    snprintf(standard, sizeof(standard), format, int32, uint32, int64, uint64, str, ptr, size_t1);
    TEST_ASSERT(0 == memcmp(target.c_str(), standard, target.size()));

    return true;
}
//---------------------------------------------------------------------------
bool Test_BinString()
{
    std::string bin(10, 'a');
    std::string bin_str = BinToString(reinterpret_cast<const unsigned char*>(bin.data()), bin.length());
    MemoryBlock bin_data = StringToBin(bin_str);
    TEST_ASSERT(0 == memcmp(bin_data.data(), bin.data(), bin.size()));
    TEST_ASSERT(bin.size() == bin_data.size());
    TEST_ASSERT(bin_str.size() == bin.size()*2);

    for(int i=0; i<256; i++)
    {
        unsigned char c = static_cast<unsigned char>(i);
        std::string s = BinToString(&c, 1);
        char buf[3];
        snprintf(buf, 3, "%02X", c);
        TEST_ASSERT(buf == s);
        MemoryBlock d = StringToBin(s);
        TEST_ASSERT(1 == d.size());
        TEST_ASSERT(static_cast<unsigned char>(d[0]) == i);
    }

    return true;
}
//---------------------------------------------------------------------------
bool Test_UpperLower()
{
    std::string standard = "abcdefg";
    std::string standard_upper = "ABCDEFG";
    std::string upper = ToUpper(standard);
    std::string lower = ToLower(upper);
    TEST_ASSERT(upper == standard_upper);
    TEST_ASSERT(standard == lower);

    return true;
}
//---------------------------------------------------------------------------
bool Test_BinChar()
{
    unsigned char dat[] = {'S','s','0','1','2','3','4','5','6','7','8','9'};
    std::string str_char = BinToChars(dat, sizeof(dat));
    MemoryBlock mb = CharsToBin(str_char);
    TEST_ASSERT(0 == memcmp(dat, mb.data(), sizeof(dat)));
    TEST_ASSERT(sizeof(dat) == mb.size());

    return true;
}
//---------------------------------------------------------------------------
bool Test_Base64()
{
    std::string dat1 = "Create an account or log into Facebook. Connect with friends, family and other people you know. Share photos and videos, send messages and get updates.";
    std::string dat2 = "Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure.";
    std::string result1 = Base64_encode(dat1.c_str(), dat1.size());
    std::string result2 = Base64_encode(dat2.c_str(), dat2.size());
    std::cout << "base64:" << result1 << std::endl;
    std::cout << "base64:" << result2 << std::endl;
    std::string std_result1 = "Q3JlYXRlIGFuIGFjY291bnQgb3IgbG9nIGludG8gRmFjZWJvb2suIENvbm5lY3Qgd2l0aCBmcmllbmRzLCBmYW1pbHkgYW5kIG90aGVyIHBlb3BsZSB5b3Uga25vdy4gU2hhcmUgcGhvdG9zIGFuZCB2aWRlb3MsIHNlbmQgbWVzc2FnZXMgYW5kIGdldCB1cGRhdGVzLg==";
    std::string std_result2 = "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRoZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=";

    TEST_ASSERT(std_result1 == result1);
    TEST_ASSERT(std_result2 == result2);

    TEST_ASSERT("TWFu" == Base64_encode("Man", 3));
    TEST_ASSERT("TWE=" == Base64_encode("Ma", 2));
    TEST_ASSERT("TQ==" == Base64_encode("M", 1));

    TEST_ASSERT(MemoryBlock({'M','a','n'}) == Base64_decode("TWFu"));
    TEST_ASSERT(MemoryBlock({'M','a'}) == Base64_decode("TWE="));
    TEST_ASSERT(MemoryBlock({'M'})  == Base64_decode("TQ=="));

    MemoryBlock mb_result1 = Base64_decode(result1);
    MemoryBlock mb_result2 = Base64_decode(result2);
    std::cout << mb_result1.data() << std::endl;
    std::cout << mb_result2.data() << std::endl;

    TEST_ASSERT(mb_result1 == MemoryBlock(dat1.begin(), dat1.begin()+dat1.length()));
    TEST_ASSERT(mb_result2 == MemoryBlock(dat2.begin(), dat2.begin()+dat2.length()));

    return true;
}
//---------------------------------------------------------------------------
bool Test_Splite()
{
    char delim = '/';
    std::string str1 = "/tmp/a/b";
    std::string str2 = "tmp/a/b/";
    std::string str3 = "tmp//b";
    std::string str4 = "//";

    std::vector<std::string> s1 = split(str1, delim);
    std::vector<std::string> s2 = split(str2, delim);
    std::vector<std::string> s3 = split(str3, delim);
    std::vector<std::string> s4 = split(str4, delim);

    TEST_ASSERT(s1 == std::vector<std::string>({"tmp", "a", "b"}));
    TEST_ASSERT(s2 == std::vector<std::string>({"tmp", "a", "b"}));
    TEST_ASSERT(s3 == std::vector<std::string>({"tmp", "b"}));
    TEST_ASSERT(s4 == std::vector<std::string>());
    
    return true;
}
//---------------------------------------------------------------------------
bool Test_RunPath()
{
    std::string run_folder = RunPathFolder();
    std::string run_name = RunExeName();
    std::string run_file_name = RunPathFileName("a.exe");
    std::cout << "run folder:" << run_folder << std::endl;
    std::cout << "run name:" << run_name << std::endl;
    std::cout << "run file name:" << run_file_name << std::endl;

    return true;
}
//---------------------------------------------------------------------------
bool Test_Path()
{
    TEST_ASSERT(false == DocumentExist(("/tmpdddd")));
    TEST_ASSERT(DocumentExist(("/tmp")));
    TEST_ASSERT(DocumentExist((("/home"))));
    TEST_ASSERT(FolderExist(("/tmp")));

    const char* path = ("/tmp/myfolder");
    FolderDelete(path);
    TEST_ASSERT(false == FolderDelete(path));
    TEST_ASSERT(FolderCreate(path, true));
    TEST_ASSERT(FolderExist(path));
    TEST_ASSERT(FolderDelete(path));
    
    const char* path1 = ("/tmp/myfolder/1/2");
    TEST_ASSERT(FolderCreate(path1, true));
    TEST_ASSERT(FolderDelete(path1));
    TEST_ASSERT(FolderDelete("/tmp/myfolder/1"));
    TEST_ASSERT(FolderDelete(path));

    return true;
}
//---------------------------------------------------------------------------
bool Test_Document()
{
    std::string path = ("/tmp/myfolder");
    FolderCreate(path, true);

    for(int i=0; i<10; i++)
    {
        SaveFile(path+"/haha.txt", "aaa", 3);
        FolderCreate(path+"/sub", false);
        path += "/sub";
    }

    TEST_ASSERT(FolderDelete("/tmp/myfolder"));
    TEST_ASSERT(false == FolderExist("/tmp/myfolder"));
    return true;
}
//---------------------------------------------------------------------------
bool Test_File()
{
    MemoryBlock mb;
    TEST_ASSERT(LoadFile("../../test/test_function.cc", &mb));

    return true; 
}
//---------------------------------------------------------------------------
bool Test_HTTPDatetime()
{
    const char* rfc822 = "Fri, 14 Jun 2019 23:50:13 GMT";
    const char* rfc850 = "Friday, 14-Jun-19 23:50:13 GMT";
    const char* isoc = "Fri Jun 14 23:50:13 2019";

    time_t t1 = ParseHTTPDatetime(rfc822);
    time_t t2 = ParseHTTPDatetime(rfc850);
    time_t t3 = ParseHTTPDatetime(isoc);

    std::string s1 = FormatHTTPDatetime(t1);
    std::string s2 = FormatHTTPDatetime(t2);
    std::string s3 = FormatHTTPDatetime(t3);
    TEST_ASSERT(s1 == rfc822);
    std::cout << "rfc850: " << s2 << std::endl;
    std::cout << "isoc: " << s3 << std::endl;

    return true;
}
//---------------------------------------------------------------------------
int main(int, char**)
{
    TestTitle();

    Test_String();
    Test_BinString();
    Test_UpperLower();
    Test_BinChar();
    Test_Base64();
    Test_Splite();
    Test_RunPath();
    Test_Path();
    Test_Document();
    Test_File();
    Test_HTTPDatetime();

    return 0;
}
//---------------------------------------------------------------------------
