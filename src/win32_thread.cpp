#include "pch.h"
#include "thread.h"
#include <intrin.h>

#define INVALID_THREAD_RESULT ((DWORD)-1)

static DWORD win32_thread_create_type(s32 type)
{
    switch(type)
    {
        case THREAD_SUSPENDED: return CREATE_SUSPENDED;
        case THREAD_IMMEDIATE:
        default: return 0;
    }
}

u64 thread_curr_id()
{
    return GetCurrentThreadId();
}

void thread_sleep(u32 ms)
{
    Sleep(ms);
}

bool thread_active(hthread handle)
{
    DWORD exitCode;
    GetExitCodeThread(handle, &exitCode);
    return exitCode == STILL_ACTIVE;
}

hthread thread_create(s32 type, ThreadEntry entry, void* userdata)
{
    return CreateThread(0, 0, (LPTHREAD_START_ROUTINE)entry, userdata, win32_thread_create_type(type), NULL);
}

void thread_resume(hthread handle)
{
    const DWORD res = ResumeThread(handle);
    ASSERT(res != INVALID_THREAD_RESULT);
}

void thread_suspend(hthread handle)
{
    const DWORD res = SuspendThread(handle);
    ASSERT(res != INVALID_THREAD_RESULT);
}

void thread_terminate(hthread handle)
{
    DWORD exitCode;
    GetExitCodeThread(handle, &exitCode);
    const BOOL res = TerminateThread(handle, exitCode);
    ASSERT(res);
}

hsemaphore semaphore_create(bool signaled)
{
    return CreateSemaphore(nullptr, (LONG)signaled, 1, nullptr);
}

void semaphore_release(hsemaphore handle)
{
    LONG prevCount;
    ReleaseSemaphore(handle, 1, &prevCount);
}

void semaphore_wait(hsemaphore handle, u32 ms)
{
    WaitForSingleObjectEx(handle, ms, FALSE);
}

void barrier_read()
{
    _ReadBarrier();
}

void barrier_write()
{
    _WriteBarrier();
}

void barrier_memory()
{
    _ReadWriteBarrier();
}

void fence_read()
{
    _mm_lfence();
}

void fence_write()
{
    _mm_sfence();
}

void fence_memory()
{
    _mm_mfence();
}

s32 atomic_swap(volatile s32* dst, s32 val)
{
    return InterlockedExchange((volatile LONG*)dst, val);
}

s32 atomic_cmp_swap(volatile s32* dst, s32 val, s32 cmp)
{
    return InterlockedCompareExchange((volatile LONG*)dst, val, cmp);
}

void* atomic_cmp_swap(volatile void** dst, void* val, void* cmp)
{
    return InterlockedCompareExchangePointer((volatile LPVOID*)dst, val, cmp);
}

s32 atomic_add(volatile s32* dst, s32 val)
{
    return InterlockedAdd((volatile LONG*)dst, val);
}

s32 atomic_inc(volatile s32* dst)
{
    return InterlockedIncrement((volatile LONG*)dst);
}

s32 atomic_dec(volatile s32* dst)
{
    return InterlockedDecrement((volatile LONG*)dst);
}
