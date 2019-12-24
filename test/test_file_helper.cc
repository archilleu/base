//---------------------------------------------------------------------------
#include "test_inc.h"
#include "../src/file_helper.h"
#include "../src/function.h"
//---------------------------------------------------------------------------
using namespace base;
using namespace base::test;
//---------------------------------------------------------------------------
bool TestIllegal()
{
    FileHelper file1;
    try
    {
        file1.Open("/");
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    FileHelper file2;
    try
    {
        file2.Open("/etc/passwd");
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return true;
}
//---------------------------------------------------------------------------
bool TestAppend()
{
    const static char* path = "/tmp/append_file";
    const static char* info1 = "god damn smart 1\n";
    const static char* info2 = "god damn smart 2\n";

    //append
    {
    FileDelete(path);

    FileHelper file;
    size_t size = strlen(info1);
    file.Open(path);
    
    for(int i=0; i<100; i++)
        file.Write(info1, size);
    file.Flush();
    size_t file_size = file.Size();
    file.Close();

    FILE* fp = fopen(path, "r");
    TEST_ASSERT(fp != nullptr);

    for(int i=0; i<100; i++)
    {
        char buffer[128];
        if(0 != fgets(buffer, 128, fp))
            TEST_ASSERT(0==strcmp(buffer, info1));
        TEST_ASSERT(0==strcmp(buffer, info1));
    }
    TEST_ASSERT(file_size == static_cast<size_t>(ftell(fp)));
    fclose(fp);

    //再次追加
    file.Open(path);
    TEST_ASSERT(file_size == file.Size());
    for(int i=0; i<100; i++)
    {
        file.Write(info2, size);
    }
    file.Flush();
    TEST_ASSERT(file_size*2 == file.Size());
    }

    //追加完成后再次检测
    FILE* fp = fopen(path, "r");
    TEST_ASSERT(fp!=0);

    for(int i=0; i<100; i++)
    {
        char buffer[128];
        if(0 != fgets(buffer, 128, fp))
            TEST_ASSERT(0==strcmp(buffer, info1));
        TEST_ASSERT(0==strcmp(buffer, info1));
    }
    for(int i=100; i<200; i++)
    {
        char buffer[128];
        if(0 != fgets(buffer, 128, fp))
            TEST_ASSERT(0==strcmp(buffer, info2));
        TEST_ASSERT(0==strcmp(buffer, info2));
    }

    fclose(fp);

    return true;
}
//---------------------------------------------------------------------------
bool TestTruncate()
{
    const static char* path = "/tmp/append_file";
    const static char* info1 = "god damn smart 1\n";
    const static char* info2 = "god damn smart 2\n";

    {
    FileDelete(path);

    FileHelper file;
    size_t size = strlen(info1);
    file.Open(path, true);
    
    for(int i=0; i<100; i++)
        file.Write(info1, size);
    file.Flush();
    size_t file_size = file.Size();
    file.Close();

    FILE* fp = fopen(path, "r");
    TEST_ASSERT(fp!=0);

    for(int i=0; i<100; i++)
    {
        char buffer[128];
        if(0 != fgets(buffer, 128, fp))
            TEST_ASSERT(0==strcmp(buffer, info1));
        TEST_ASSERT(0==strcmp(buffer, info1));
    }
    TEST_ASSERT(file_size == static_cast<size_t>(ftell(fp)));
    fclose(fp);

    //再次截断
    file.Open(path, true);
    TEST_ASSERT(0 == file.Size());
    for(int i=0; i<100; i++)
    {
        file.Write(info2, size);
    }
    file.Flush();
    TEST_ASSERT(file_size == file.Size());
    }

    //追加完成后再次检测
    FILE* fp = fopen(path, "r");
    TEST_ASSERT(fp!=0);

    for(int i=0; i<100; i++)
    {
        char buffer[128];
        if(0 != fgets(buffer, 128, fp))
            TEST_ASSERT(0==strcmp(buffer, info2));
        TEST_ASSERT(0==strcmp(buffer, info2));
    }

    fclose(fp);

    return true;
}
//---------------------------------------------------------------------------
void TestReadWritePeek()
{
    const std::string s = "string";
    int8_t int8 = 8;
    int16_t int16 = 16;
    int32_t int32 = 32;
    int64_t int64 = 64;
    const static char* path = "/tmp/read_file";

    FileDelete(path);

    {
    FileHelper file;
    file.Open(path);
    file.Write(s);
    file.Write(int8);
    file.Write(int16);
    file.Write(int32);
    file.Write(int64);
    }

    {
    FileHelper file;
    file.Open(path);
    TEST_ASSERT(s == file.PeekString(s.length()));
    TEST_ASSERT(s == file.ReadString(s.length()));
    TEST_ASSERT(int8 == file.PeekInt8());
    TEST_ASSERT(int8 == file.ReadInt8());
    TEST_ASSERT(int16 == file.PeekInt16());
    TEST_ASSERT(int16 == file.ReadInt16());
    TEST_ASSERT(int32 == file.PeekInt32());
    TEST_ASSERT(int32 == file.ReadInt32());
    TEST_ASSERT(int64 == file.PeekInt64());
    TEST_ASSERT(int64 == file.ReadInt64());
    }

}
//---------------------------------------------------------------------------
int main(int, char**)
{
    TestTitle();

    TestIllegal();
    TestAppend();
    TestTruncate();
    TestReadWritePeek();

    return 0;
}
//---------------------------------------------------------------------------
