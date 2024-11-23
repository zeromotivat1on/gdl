#include "pch.h"
#include "mem.h"

void* vm_reserve(void* addr, u64 size)
{
    PANIC(size == 0);
    return VirtualAlloc(addr, size, MEM_RESERVE, PAGE_READWRITE);
}

void* vm_commit(void* vm, u64 size)
{
    PANIC(!vm || size == 0);
    return VirtualAlloc(vm, size, MEM_COMMIT, PAGE_READWRITE);
}

bool vm_decommit(void* vm, u64 size)
{
    PANIC(!vm || size == 0)
    return VirtualFree(vm, size, MEM_DECOMMIT);
}

bool vm_release(void* vm)
{
    PANIC(!vm);
    return VirtualFree(vm, 0, MEM_RELEASE);
}
