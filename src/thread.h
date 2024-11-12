#pragma once

// ------
// Thread
// ------

#define THREAD_IMMEDIATE    0
#define THREAD_SUSPENDED    1

typedef void*	hthread; // thread handle
typedef u32     (*ThreadEntry)(void*);

u64         thread_curr_id();
void        thread_sleep(u32 ms);
bool        thread_active(hthread handle);

hthread		thread_create(s32 type, ThreadEntry entry, void* userdata);
void        thread_resume(hthread handle);
void        thread_suspend(hthread handle);
void        thread_terminate(hthread handle);

// ---------
// Semaphore
// ---------

#define SEMAPHORE_MAX_WAIT_TIME 0xFFFFFFFFu

typedef void*	hsemaphore; // semaphore handle

hsemaphore  semaphore_create(bool signaled);
void        semaphore_release(hsemaphore handle);
void        semaphore_wait(hsemaphore handle, u32 ms);

// -------
// Barrier
// -------

// Hint compiler to not reorder memory operations, happened before barrier.
// Basically disable memory read/write concerned optimizations.

void		barrier_read();
void		barrier_write();
void		barrier_memory();

// -----
// Fence
// -----

// Ensure the order of read/write CPU instructions.

void		fence_read();
void		fence_write();
void		fence_memory();

// ------
// Atomic
// ------

// Atomic operations ensure that only one thread can execute them at specific point of time.

s32			atomic_swap(volatile s32* dst, s32 val); // swap dst and val and return dst before op

// If dst is equal to cmp, set dst to val, otherwise do nothing, return dst before op.
s32			atomic_cmp_swap(volatile s32* dst, s32 val, s32 cmp);
void*		atomic_cmp_swap(volatile void** dst, void* val, void* cmp);

s32			atomic_add(volatile s32* dst, s32 val); // add val to dst and return dst before op
s32			atomic_inc(volatile s32* dst);  // atomic increment
s32			atomic_dec(volatile s32* dst);  // atomic decrement
