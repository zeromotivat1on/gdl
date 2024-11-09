#pragma once

// ------
// Thread
// ------

#define THREAD_IMMEDIATE    0
#define THREAD_SUSPENDED    1

typedef void*   thhandle; // thread handle
typedef u32     (*thentry)(void*);

u64         thcurrid();
void        thsleep(u32 ms);
bool        thactive(thhandle handle);

thhandle    thcreate(s32 type, thentry entry, void* userdata);
void        thresume(thhandle handle);
void        thsuspend(thhandle handle);
void        thterminate(thhandle handle);

// ---------
// Semaphore
// ---------

#define SM_MAX_WAIT_TIME    0xFFFFFFFFu

typedef void*   smhandle; // semaphore handle

smhandle    smcreate(bool signaled);
void        smrelease(smhandle handle);
void        smwait(smhandle handle, u32 ms);

// -------
// Barrier
// -------

// Hint compiler to not reorder memory operations, happened before barrier.
// Basically disable memort read/write concerned optimizations.

void    rbarrier(); // barrier for read/load ops
void    wbarrier(); // barrier for write/store ops
void    mbarrier(); // barrier for read/load and write/store ops

// -----
// Fence
// -----

// Ensure the order of read/write CPU instructions.

void    rfence();   // fence for read/load ops
void    wfence();   // fence for write/store ops
void    mfence();   // fence for read/load and write/store ops

// ------
// Atomic
// ------

// Atomic operations ensure that only one thread can execute them at specific point of time.

s32     atmswap(volatile s32* dst, s32 val); // swap dst and val and return dst before op

// If dst is equal to cmp, set dst to val, otherwise do nothing, return dst before op.
s32     atmcmpswap(volatile s32* dst, s32 val, s32 cmp);
void*   atmcmpswap(volatile void** dst, void* val, void* cmp);

s32     atmadd(volatile s32* dst, s32 val); // add val to dst and return dst before op
s32     atminc(volatile s32* dst);  // atomic increment
s32     atmdec(volatile s32* dst);  // atomic decrement
