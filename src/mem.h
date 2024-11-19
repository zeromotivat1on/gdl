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
void*   mem_virt_reserve(void* addr, u64 size);

// Commit virtual memory from given reserved range.
// Physical memory is allocated when commited one is being written to.
void*   mem_virt_commit(void* vm, u64 size);

// Release physical memory from given range of virtual addresses.
bool    mem_virt_decommit(void* vm, u64 size);

// Free both physical and virtual memory.
bool    mem_virt_release(void* vm);

// ------------
// Memory arena
// ------------

struct Arena
{
    u8* base;
    u64 size;
    u64 used;
};

#define arena_push_size(arena, size)            (u8*)arena_push_zero(arena, size)
#define arena_push_struct(arena, type)          (type*)arena_push_zero(arena, sizeof(type))
#define arena_push_array(arena, count, type)    (type*)arena_push_zero(arena, sizeof(type) * count)

inline void arena_init(Arena* arena, void* base, u64 size)
{
    arena->base = (u8*)base;
    arena->size = size;
    arena->used = 0;
}

inline Arena arena_create(void* base, u64 size)
{
    Arena arena = STRUCT_ZERO(Arena);
    arena_init(&arena, base, size);
    return arena;
}

inline void* arena_push(Arena* arena, u64 size)
{
    PANIC(arena->used + size > arena->size);
    void* data = arena->base + arena->used;
    arena->used += size;
    return data;
}

inline void* arena_push_zero(Arena* arena, u64 size)
{
    void* data = arena_push(arena, size);
    memset(data, 0, size);
    return data;
}

inline void arena_pop(Arena* arena, u64 size)
{
    PANIC(arena->used < size);
    arena->used -= size;
}

inline void arena_clear(Arena* arena)
{
    arena->used = 0;
}
