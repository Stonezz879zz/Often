#include "CMemoryUsage.h"
#include <Windows.h>

int CMemoryUsage::GetMemoryUsage()
{
    //获取内存利用率
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    auto m_memory_usage = statex.dwMemoryLoad;
    auto m_used_memory = static_cast<int>((statex.ullTotalPhys - statex.ullAvailPhys) / 1024);
    auto m_total_memory = static_cast<int>(statex.ullTotalPhys / 1024);
    return m_used_memory*100 / m_total_memory % 100;
    //return 0;
}
