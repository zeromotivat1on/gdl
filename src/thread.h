#pragma once

#define WAIT_INFINITE       0xFFFFFFFF

// ------
// Thread
// ------

extern const s32 THREAD_CREATE_IMMEDIATE;
extern const s32 THREAD_CREATE_SUSPENDED;

typedef void*	thread_handle;
typedef u32     (*thread_entry)(void*);

u64				current_thread_id();
void			sleep_thread(u32 ms);
bool			is_thread_active(thread_handle handle);

thread_handle	create_thread(thread_entry entry, void* userdata, s32 create_type);
void			resume_thread(thread_handle handle);
void			suspend_thread(thread_handle handle);
void			terminate_thread(thread_handle handle);

// ---------
// Semaphore
// ---------

typedef void*	semaphore_handle;

semaphore_handle	create_semaphore(s32 init_count, s32 max_count);
bool				release_semaphore(semaphore_handle handle, s32 count, s32* prev_count);
bool				wait_semaphore(semaphore_handle handle, u32 ms);

// -----
// Mutex
// -----

typedef void*   mutex_handle;

mutex_handle	create_mutex(bool signaled);
bool			release_mutex(mutex_handle handle);
bool			wait_mutex(mutex_handle handle, u32 ms);

// ----------------
// Critical Section
// ----------------

extern const u32 CRITICAL_SECTION_ALLOC_SIZE;

typedef void*   critical_section_handle;

// Initialize critical section in preallocated memory with optional spin lock counter.
// If spin_count <= 0, wait for critical section will always put calling thread to sleep.
// If thread tries to acquire locked critical section with spin lock,
// thread spins in a loop spin_count times checking if lock is released.
// If lock is not released at the end of spin loop, thread is put to sleep.
void        init_critical_section(critical_section_handle handle, u32 spin_count);
void        enter_critical_section(critical_section_handle handle);
bool        try_enter_critical_section(critical_section_handle handle);
void        leave_critical_section(critical_section_handle handle);
void        delete_critical_section(critical_section_handle handle);

// -------
// Barrier
// -------

// Hint compiler to not reorder memory operations, happened before barrier.
// Basically disable memory read/write concerned optimizations.

void		read_barrier();
void		write_barrier();
void		memory_barrier();

// -----
// Fence
// -----

// Ensure the order of read/write CPU instructions.

void		read_fence();
void		write_fence();
void		memory_fence();

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
