#pragma once

// ------
// System
// ------

struct Sys_Mem_Status
{
    u64 phys_total;
    u64 phys_avail;
    u64 virt_total;
    u64 virt_avail;
};

struct Sys_Info
{
    u32 page_size;
    u32 alloc_gran;
    u32 lg_core_num;
};

void sys_mem_status(Sys_Mem_Status* status);
void sys_info(Sys_Info* info);
