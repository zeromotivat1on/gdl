#pragma once

// ------
// Macros
// ------

// To bytes conversion.

#define KB(n)   (n * 1024ull)
#define MB(n)   (KB(n) * 1024ull)
#define GB(n)   (MB(n) * 1024ull)
#define TB(n)   (GB(n) * 1024ull)

// --------------
// Virtual memory
// --------------

// Reserve virtual memory of a given size.
// Returned memory and alloc size are aligned based on system granularity.
// Initial address can be specified, leave null to let the os decide.
void*   vm_reserve(void* addr, u64 size);

// Commit virtual memory from given reserved range.
// Physical memory is allocated when commited one is being written to.
void*   vm_commit(void* vm, u64 size);

// Release physical memory from given range of virtual addresses.
bool    vm_decommit(void* vm, u64 size);

// Free both physical and virtual memory.
bool    vm_release(void* vm);

// ------------
// Memory arena
// ------------

struct Arena
{
    u8*     base;
    u64     size;
    u64     used;

    void    init(void* base, u64 size);
    void    clear();
    void*   push(u64 size);
    void*   push_zero(u64 size);
    void    pop(u64 size);
};

#define arena_push_size(arena, size)            (u8*)arena->push_zero(size)
#define arena_push_struct(arena, type)          (type*)arena->push_zero(sizeof(type))
#define arena_push_array(arena, count, type)    (type*)arena->push_zero(sizeof(type) * count)

inline void Arena::init(void* base, u64 size)
{
    this->base = (u8*)base;
    this->size = size;
    this->used = 0;
}

inline void Arena::clear()
{
    used = 0;
}

inline void* Arena::push(u64 size)
{
    ASSERT(used + size <= this->size);
    void* data = base + used;
    used += size;
    return data;
}

inline void* Arena::push_zero(u64 size)
{
    void* data = push(size);
    memset(data, 0, size);
    return data;
}

inline void Arena::pop(u64 size)
{
    ASSERT(used >= size);
    used -= size;
}
