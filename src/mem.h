#pragma once

// ------
// Macros
// ------

// To bytes conversion.

#define KB(n)   (n * 1024ull)
#define MB(n)   (KB(n) * 1024ull)
#define GB(n)   (MB(n) * 1024ull)
#define TB(n)   (GB(n) * 1024ull)

// ------
// System
// ------

struct MemStatus
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

void sysmemstatus(MemStatus* status);
void sysinfo(SysInfo* info);

// --------------
// Virtual memory
// --------------

// Reserve virtual memory of a given size.
// Returned memory and alloc size are aligned based on system granularity.
// Initial address can be specified, leave null to let the os decide.
void*   vmreserve(void* addr, u64 size);

// Commit virtual memory from given reserved range.
// Physical memory is allocated when commited one is being written to.
void*   vmcommit(void* vm, u64 size);

// Release physical memory from given range of virtual addresses.
bool    vmdecommit(void* vm, u64 size);

// Free both physical and virtual memory.
bool    vmrelease(void* vm);

// ------------
// Memory arena
// ------------

struct Arena
{
    u8* Base;
    u64 Size;
    u64 Used;
};

// Push size bytes.
#define mpushsize(arena, size)          (u8*)mpushzero(arena, size)

// Push specific type.
#define mpushtype(arena, type)          (type*)mpushzero(arena, sizeof(type))

// Push array of types.
#define mpusharr(arena, type, count)    (type*)mpushzero(arena, sizeof(type) * count)

inline void* mpush(Arena* arena, u64 size)
{
    ASSERT(arena->Used + size <= arena->Size);
    void* data = arena->Base + arena->Used;
    arena->Used += size;
    return data;
}

inline void* mpushzero(Arena* arena, u64 size)
{
    void* data = mpush(arena, size);
    memset(data, 0, size);
    return data;
}

inline void mpop(Arena* arena, u64 size)
{
    ASSERT(arena->Used >= size);
    arena->Used -= size;
}
