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

static BOOL win32_wait_res_check(void* hobj, DWORD res)
{
    switch(res)
    {
        case WAIT_OBJECT_0:
            return true;

        case WAIT_ABANDONED:
            msg_error("[gdl]: Object (%p) was not released before owning thread termination", hobj);
            return false;
            
        case WAIT_TIMEOUT:
            msg_warning("[gdl]: Wait time for object (%p) elapsed", hobj);
            return false;
            
        case WAIT_FAILED:
            msg_error("[gdl]: Failed to wait for object (%p) with error code (%u)", hobj, GetLastError());
            return false;
                        
        default:
            msg_error("[gdl]: Unknown wait result (%u) for object (%p)", res, hobj);
            return false;
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
    DWORD exit_code;
    GetExitCodeThread(handle, &exit_code);
    return exit_code == STILL_ACTIVE;
}

hthread thread_create(s32 type, ThreadEntry entry, void* userdata)
{
    return CreateThread(0, 0, (LPTHREAD_START_ROUTINE)entry, userdata, win32_thread_create_type(type), NULL);
}

void thread_resume(hthread handle)
{
    const DWORD res = ResumeThread(handle);
    PANIC(res == INVALID_THREAD_RESULT);
}

void thread_suspend(hthread handle)
{
    const DWORD res = SuspendThread(handle);
    PANIC(res == INVALID_THREAD_RESULT);
}

void thread_terminate(hthread handle)
{
    DWORD exit_code;
    GetExitCodeThread(handle, &exit_code);
    const BOOL res = TerminateThread(handle, exit_code);
    PANIC(!res);
}

hsemaphore semaphore_create(s32 init_count, s32 max_count)
{
    return CreateSemaphore(NULL, (LONG)init_count, (LONG)max_count, NULL);
}

bool semaphore_release(hsemaphore handle, s32 count, s32* prev_count)
{
    return ReleaseSemaphore(handle, count, (LPLONG)prev_count);
}

bool semaphore_wait(hsemaphore handle, u32 ms)
{
    const DWORD res = WaitForSingleObjectEx(handle, ms, FALSE);
    return win32_wait_res_check(handle, res);
}

hmutex mutex_create(bool signaled)
{
    return CreateMutex(NULL, (LONG)signaled, NULL);
}

bool mutex_release(hmutex handle)
{
    return ReleaseMutex(handle);
}

bool mutex_wait(hmutex handle, u32 ms)
{
    const DWORD res = WaitForSingleObjectEx(handle, ms, FALSE);
    return win32_wait_res_check(handle, res);
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
