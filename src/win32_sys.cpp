#include "pch.h"
#include "sys.h"

void sysmemstatus(SysMemStatus* status)
{
    if (!status) return;

    MEMORYSTATUSEX ms = STRUCT_ZERO(MEMORYSTATUSEX);
    ms.dwLength = sizeof(ms);
    if (GlobalMemoryStatusEx(&ms))
    {
        status->TotalPhys = ms.ullTotalPhys;
        status->TotalVirt = ms.ullTotalVirtual;
        status->AvailPhys = ms.ullAvailPhys;
        status->AvailVirt = ms.ullAvailVirtual;
    }
}

void sysinfo(SysInfo* info)
{
    if (!info) return;

    SYSTEM_INFO si = STRUCT_ZERO(SYSTEM_INFO);
    GetSystemInfo(&si);

    info->PageSize = si.dwPageSize;
    info->AllocGran = si.dwAllocationGranularity;
    info->LgCoreNum = si.dwNumberOfProcessors;
}
