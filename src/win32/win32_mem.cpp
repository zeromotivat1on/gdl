#include "pch.h"
#include "mem.h"

void* vmreserve(void* dst, void* addr, u64 size)
{
    return VirtualAlloc(addr, size, MEM_RESERVE, PAGE_READWRITE);
}

void* vmcommit(void* dst, void* vm, u64 size)
{
    return VirtualAlloc(vm, size, MEM_COMMIT, PAGE_READWRITE);
}

bool vmdecommit(void* vm, u64 size)
{
    return VirtualFree(vm, size, MEM_DECOMMIT);
}

bool vmrelease(void* vm)
{
    return VirtualFree(vm, 0, MEM_RELEASE);
}
