#include "pch.h"
#include "mem.h"

void* mem_virt_reserve(void* addr, u64 size)
{
    PANIC(size == 0);
    return VirtualAlloc(addr, size, MEM_RESERVE, PAGE_READWRITE);
}

void* mem_virt_commit(void* vm, u64 size)
{
    PANIC(!vm || size == 0);
    return VirtualAlloc(vm, size, MEM_COMMIT, PAGE_READWRITE);
}

bool mem_virt_decommit(void* vm, u64 size)
{
    PANIC(!vm || size == 0)
    return VirtualFree(vm, size, MEM_DECOMMIT);
}

bool mem_virt_release(void* vm)
{
    PANIC(!vm);
    return VirtualFree(vm, 0, MEM_RELEASE);
}
