#pragma once

#define WAIT_INFINITE       0xFFFFFFFF

// ------
// Thread
// ------

extern const s32 THREAD_CREATE_IMMEDIATE;
extern const s32 THREAD_CREATE_SUSPENDED;

typedef void*	hthread; // thread handle
typedef u32     (*ThreadEntry)(void*);

u64         thread_curr_id();
void        thread_sleep(u32 ms);
bool        thread_active(hthread handle);

hthread		thread_create(ThreadEntry entry, void* userdata, s32 create_type);
void        thread_resume(hthread handle);
void        thread_suspend(hthread handle);
void        thread_terminate(hthread handle);

// ---------
// Semaphore
// ---------

typedef void*	hsemaphore; // semaphore handle

hsemaphore  semaphore_create(s32 init_count, s32 max_count);
bool        semaphore_release(hsemaphore handle, s32 count, s32* prev_count);
bool        semaphore_wait(hsemaphore handle, u32 ms);

// -----
// Mutex
// -----

typedef void*   hmutex;

hmutex      mutex_create(bool signaled);
bool        mutex_release(hmutex handle);
bool        mutex_wait(hmutex handle, u32 ms);

// ----------------
// Critical Section
// ----------------

extern const u32 CRITICAL_SECTION_ALLOC_SIZE;

typedef void*   hcritsec;  // critical section handle

// Initialize critical section in preallocated memory with optional spin lock counter.
// If spin_count <= 0, wait for critical section will always put calling thread to sleep.
// If thread tries to acquire locked critical section with spin lock,
// thread spins in a loop spin_count times checking if lock is released.
// If lock is not released at the end of spin loop, thread is put to sleep.
void        critical_section_init(hcritsec handle, u32 spin_count);
void        critical_section_enter(hcritsec handle);
bool        critical_section_try_enter(hcritsec handle);
void        critical_section_leave(hcritsec handle);
void        critical_section_delete(hcritsec handle);

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
s32			atomic_increment(volatile s32* dst);
s32			atomic_decrement(volatile s32* dst);
