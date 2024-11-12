#pragma once

// ------
// System
// ------

struct SysMemStatus
{
    u64 phys_total;
    u64 phys_avail;
    u64 virt_total;
    u64 virt_avail;
};

struct SysInfo
{
    u32 page_size;
    u32 alloc_gran;
    u32 lg_core_num;
};

void sys_mem_status(SysMemStatus* status);
void sys_info(SysInfo* info);
