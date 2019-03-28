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
        TEST_ASSERT(true == file.Write(info1, size));
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
        TEST_ASSERT(true == file.Write(info2, size));
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
        TEST_ASSERT(true == file.Write(info1, size));
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
        TEST_ASSERT(true == file.Write(info2, size));
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
int main(int, char**)
{
    TestTitle();

    TestIllegal();
    TestAppend();
    TestTruncate();

    return 0;
}
//---------------------------------------------------------------------------
