#include "pch.h"
#include "mem.h"

void sysmstatus(MemStatus* status)
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

void* vmreserve(void* addr, u64 size)
{
    ASSERT(size > 0);
    return VirtualAlloc(addr, size, MEM_RESERVE, PAGE_READWRITE);
}

void* vmcommit(void* vm, u64 size)
{
    ASSERT(vm && size > 0);
    return VirtualAlloc(vm, size, MEM_COMMIT, PAGE_READWRITE);
}

bool vmdecommit(void* vm, u64 size)
{
    ASSERT(vm && size > 0)
    return VirtualFree(vm, size, MEM_DECOMMIT);
}

bool vmrelease(void* vm)
{
    ASSERT(vm);
    return VirtualFree(vm, 0, MEM_RELEASE);
}
