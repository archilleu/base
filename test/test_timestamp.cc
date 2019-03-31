//---------------------------------------------------------------------------
#include "test_inc.h"
#include "../src/timestamp.h"
//---------------------------------------------------------------------------
using namespace base;
using namespace base::test;
//---------------------------------------------------------------------------
int main(int, char**)
{
    std::cout << "Invalid time:" << Timestamp::Invalid().Datetime(true)<< std::endl;

    Timestamp now = Timestamp::Now();
    uint64_t seconds = now.Microseconds();

    std::string time1 = now.Time();
    std::string time2 = now.Date();
    std::string time3 = now.Datetime();
    std::string time4 = now.Datetime(true);

    std::cout << "time:" << time1 << std::endl;
    std::cout << "date:" << time2 << std::endl;
    std::cout << "datetime:" << time3 << std::endl;
    std::cout << "datetime(ms):" << time4 << std::endl;

    Timestamp t1(seconds);
    assert(time1 == t1.Time());
    assert(time2 == t1.Date());
    assert(time3 == t1.Datetime());
    assert(time4 == t1.Datetime(true));

    TEST_ASSERT(time1 == t1.Time());
    TEST_ASSERT(time2 == t1.Date());
    TEST_ASSERT(time3 == t1.Datetime());
    TEST_ASSERT(time4 == t1.Datetime(true));

    t1.AddTime(5);
    std::string time_add = t1.Datetime(true);
    std::cout << "add time:" <<  time_add << std::endl;

    TEST_ASSERT(now < t1);
    TEST_ASSERT(now != t1);
    TEST_ASSERT(t1 > now);

    t1.ReduceTime(5);
    TEST_ASSERT(now == t1);

    return 0;
}
//---------------------------------------------------------------------------
