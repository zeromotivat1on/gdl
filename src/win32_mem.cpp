#include "pch.h"
#include "mem.h"

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
