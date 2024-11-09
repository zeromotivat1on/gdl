#pragma once

// ------
// System
// ------

struct SysMemStatus
{
    u64 TotalPhys;
    u64 TotalVirt;
    u64 AvailPhys;
    u64 AvailVirt;
};

struct SysInfo
{
    u32 PageSize;
    u32 AllocGran;
    u32 LgCoreNum;
};

void sysmemstatus(SysMemStatus* status);
void sysinfo(SysInfo* info);
