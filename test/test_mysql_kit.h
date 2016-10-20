//---------------------------------------------------------------------------
#ifndef BASE_TEST_TEST_MYSQL_KIT_H_
#define BASE_TEST_TEST_MYSQL_KIT_H_
//---------------------------------------------------------------------------
#include "test_base.h"
//---------------------------------------------------------------------------
namespace base
{

namespace test
{

class TestMysqlKit : public TestBase
{
public:
    TestMysqlKit()
    {
    }
    virtual ~TestMysqlKit()
    {
    }

    virtual bool DoTest();

private:
    bool TestNormal();
};

}//namespace base

}//namespace test
//---------------------------------------------------------------------------
#endif //BASE_TEST_TEST_MYSQL_KIT_H_
