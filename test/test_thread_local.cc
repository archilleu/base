//---------------------------------------------------------------------------
#include "test_inc.h"
#include "../src/function.h"
#include "../src/thread.h"
#include "../src/thread_local.h"
//---------------------------------------------------------------------------
using namespace base;
using namespace base::test;
//---------------------------------------------------------------------------
class TestThreadLocal
{
public:
    TestThreadLocal()
    :   thread1_(std::bind(&TestThreadLocal::OnThread1, this)),
        thread2_(std::bind(&TestThreadLocal::OnThread2, this))
    {
    }

    bool Test_Normal();

private:
    void OnThread1();
    void OnThread2();

private:
    Thread thread1_;
    Thread thread2_;

    std::set<std::string> set1_;
    std::set<std::string> set2_;
    ThreadLocal<std::set<std::string>> tls_;
};
//---------------------------------------------------------------------------
bool TestThreadLocal::Test_Normal()
{
    set1_.insert("1");
    for(size_t i=0; i<1000*100; i++)
    {
        set1_.insert(base::CombineString("%zu", i));
        set2_.insert(base::CombineString("%zu", i+1000*100));
    }

    thread1_.Start();
    thread2_.Start();
    thread1_.Join();
    thread2_.Join();

    tls_.value().insert("aaa");
    TEST_ASSERT(*(tls_.value().begin()) == "aaa");
    std::cout << *(tls_.value().begin()) << std::endl;

    return true;
}
//---------------------------------------------------------------------------
void TestThreadLocal::OnThread1()
{
    for(auto iter : set1_)
    {
        tls_.value().insert(iter);
    }

    for(auto iter : set1_)
    {
        tls_.value().erase(iter);
    }

    std::cout << "1:" << tls_.value().size() << std::endl;
    assert(0 == tls_.value().size());
    return;
}
//---------------------------------------------------------------------------
void TestThreadLocal::OnThread2()
{
    for(auto iter : set2_)
    {
        tls_.value().insert(iter);
    }

    for(auto iter : set2_)
    {
        tls_.value().erase(iter);
    }

    std::cout << "2:" << tls_.value().size() << std::endl;
    assert(0 == tls_.value().size());
    return;
}
//---------------------------------------------------------------------------
int main(int, char**)
{
    TestTitle();

    TestThreadLocal local;
    local.Test_Normal();
    return 0;
}
