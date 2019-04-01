//---------------------------------------------------------------------------
#include "test_inc.h"
#include "../src/thread.h"
//---------------------------------------------------------------------------
using namespace base;
using namespace base::test;
//---------------------------------------------------------------------------
class TestThread
{
public:
    TestThread()
    :   thread1_(std::bind(&TestThread::Thread_Func1, this)),
        thread2_(std::bind(&TestThread::Thread_Func1, this))
    {
        atomic_ = 0;
    }
    ~TestThread()
    {}

    bool Test_ParamClass();

private:
    void Thread_Func1();
    
    int count_;
    std::mutex mutex_;
    std::atomic<int> atomic_;

    Thread thread1_;
    Thread thread2_;

    static const int TIMES = 1024*1024*1024;
};
//---------------------------------------------------------------------------
void TestThread::Thread_Func1()
{
    for(int i=0; i<TestThread::TIMES/2; i++)
    {
        atomic_++;

        std::lock_guard<std::mutex> lock(mutex_);
        count_++;
    }

    return;
}
//---------------------------------------------------------------------------
bool TestThread::Test_ParamClass()
{
    count_ = 0;  

    TEST_ASSERT(thread1_.Start());
    TEST_ASSERT(thread2_.Start());

    std::cerr << "test long time, please wait" << std::endl;
    thread1_.Join();
    thread2_.Join();

    TEST_ASSERT(TestThread::TIMES == count_);
    TEST_ASSERT(TestThread::TIMES == atomic_);
    return true;
}
//---------------------------------------------------------------------------
void ThreadFunc_None()
{
    std::cout << "tid:" << CurrentThread::tid() << std::endl;
    std::cout << "tid str:" << CurrentThread::tid_str() << std::endl;
    std::cout << "thread name::" << CurrentThread::tname() << std::endl;
}
//---------------------------------------------------------------------------
void Thread_Func_ParanNone()
{
    sleep(5);
}
//---------------------------------------------------------------------------
void Thread_Func_ParamTow(int num, int* count)
{
    for(int i=0; i<10; i++)
    {
        num++;
        (*count)++;
    }

    return;
}
//---------------------------------------------------------------------------
bool Test_None()
{
    Thread t1(ThreadFunc_None);
    TEST_ASSERT(t1.Start());

    std::cout << "fname:" << t1.name() << std::endl;
    std::cout << "fid:" << t1.tid() << std::endl;;

    t1.Join();
    return true;
}
//---------------------------------------------------------------------------
bool Test_ParamNone()
{
    Thread t1(ThreadFunc_None);
    Thread t2(ThreadFunc_None);
    Thread t3(ThreadFunc_None);
    t1.Start();
    t2.Start();
    TEST_ASSERT(t3.Start());
    t1.Join();
    t2.Join();
    t3.Join();

    return true;
}
//---------------------------------------------------------------------------
bool Test_Param1()
{
    int num = 0;
    int count = 0;

    Thread t(std::bind(Thread_Func_ParamTow, num, &count));
    TEST_ASSERT(t.Start());
    t.Join();

    TEST_ASSERT(0 == num);
    TEST_ASSERT(10 == count);

    return true;
}
//---------------------------------------------------------------------------
bool Test_100_thread()
{
    for(int i=0; i<100; i++)
    {
        Thread t(ThreadFunc_None);
        t.Start();
        t.Join();
    }

    return true;
}
//---------------------------------------------------------------------------
int main(int, char**)
{
    TestTitle();

    Test_None();
    Test_ParamNone();
    Test_Param1();
    Test_100_thread();

    TestThread test_thread;
    test_thread.Test_ParamClass();

    return 0;
}
//---------------------------------------------------------------------------
