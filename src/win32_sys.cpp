#include "pch.h"
#include "sys.h"

void sys_mem_status(Sys_Mem_Status* status)
{
    if (!status) return;

    MEMORYSTATUSEX ms = STRUCT_ZERO(MEMORYSTATUSEX);
    ms.dwLength = sizeof(ms);
    if (GlobalMemoryStatusEx(&ms))
    {
        status->phys_total = ms.ullTotalPhys;
        status->virt_total = ms.ullTotalVirtual;
        status->phys_avail = ms.ullAvailPhys;
        status->virt_avail = ms.ullAvailVirtual;
    }
}

void sys_info(Sys_Info* info)
{
    if (!info) return;

    SYSTEM_INFO si = STRUCT_ZERO(SYSTEM_INFO);
    GetSystemInfo(&si);

    info->page_size = si.dwPageSize;
    info->alloc_gran = si.dwAllocationGranularity;
    info->lg_core_num = si.dwNumberOfProcessors;
}
