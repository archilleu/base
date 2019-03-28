//---------------------------------------------------------------------------
#include "test_inc.h"
#include "../src/computer_info.h"
//---------------------------------------------------------------------------
using namespace base;
using namespace base::test;
//---------------------------------------------------------------------------
bool Test_Normal()
{
    //computer description
    {
    ComputerInfo::ComputerName name = ComputerInfo::GetComputerName();
    std::cout << "systeem name:" << name.sysname << std::endl <<
        "net name:" << name.netname << std::endl <<
        "release:" << name.release << std::endl <<
        "version" << name.version << std::endl <<
        "machine:" << name.machine << std::endl;
    }

    //filesystem
    {
    std::vector<ComputerInfo::DiskspaceInfo> info = ComputerInfo::GetDiskspaceInfo();
    std::cout << "filesystem " << "mount point" << "used " << "total " << std::endl;
    for(auto iter : info)
    {
        std::cout << iter.filesystem << "mount_point:" << iter.mount_point
            << "\t" << "used(kb):" << iter.used/1024
            << "\t(total(kb):" << iter.total/1024<< std::endl;
    }

    }

    //memory
    {
    ComputerInfo::MemoryInfo mem = ComputerInfo::GetMemoryInfo();
    std::cout << "mem_total:" << mem.mem_total << " mem_free: " << mem.mem_free << " swap_total:" << mem.swap_total << " swap_free: " << mem.swap_free << std::endl;
    }

    //cpu info
    {
    ComputerInfo::CPUInfo cpu = ComputerInfo::GetCPUInfo();
    std::cout << "cpu info:" << std::endl;
    std::cout << "vender:" << cpu.vender << std::endl <<
        "model name:" << cpu.modle_name << std::endl <<
        "MHz: " << cpu.MHz << std::endl <<
        "sockets:" << cpu.sockets << std::endl <<
        "core_per_socket:" << cpu.core_per_socket << std::endl <<
        "thread_per_core:" << cpu.thread_per_core << std::endl;

    ComputerInfo::InitCPUUsage();
    for(int i=0; i<10; i++)
    {
        std::cout<< "current usage:" << ComputerInfo::GetCPUUsage() << std::endl;
        sleep(1);
    }
    }

    return true;
}
//---------------------------------------------------------------------------
int main(int, char**)
{
    TestTitle();

    Test_Normal();
    return 0;
}
//---------------------------------------------------------------------------
