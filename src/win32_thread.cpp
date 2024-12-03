#include "pch.h"
#include "thread.h"
#include <intrin.h>

#define INVALID_THREAD_RESULT ((DWORD)-1)

const u32 CRITICAL_SECTION_ALLOC_SIZE = sizeof(CRITICAL_SECTION);

const s32 THREAD_CREATE_IMMEDIATE = 0;
const s32 THREAD_CREATE_SUSPENDED = CREATE_SUSPENDED;

static BOOL win32_wait_res_check(void* hobj, DWORD res)
{
    switch(res)
    {
        case WAIT_OBJECT_0:
            return true;

        case WAIT_ABANDONED:
            msg_error("[gdl]: Mutex (%p) was not released before owning thread termination", hobj);
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

u64 current_thread_id()
{
    return GetCurrentThreadId();
}

void sleep_thread(u32 ms)
{
    Sleep(ms);
}

bool is_thread_active(thread_handle handle)
{
    DWORD exit_code;
    GetExitCodeThread(handle, &exit_code);
    return exit_code == STILL_ACTIVE;
}

thread_handle create_thread(thread_entry entry, void* userdata, s32 create_type)
{
    return CreateThread(0, 0, (LPTHREAD_START_ROUTINE)entry, userdata, create_type, NULL);
}

void resume_thread(thread_handle handle)
{
    const DWORD res = ResumeThread(handle);
    PANIC(res == INVALID_THREAD_RESULT);
}

void suspend_thread(thread_handle handle)
{
    const DWORD res = SuspendThread(handle);
    PANIC(res == INVALID_THREAD_RESULT);
}

void terminate_thread(thread_handle handle)
{
    DWORD exit_code;
    GetExitCodeThread(handle, &exit_code);
    const BOOL res = TerminateThread(handle, exit_code);
    ASSERT(res);
}

semaphore_handle create_semaphore(s32 init_count, s32 max_count)
{
    return CreateSemaphore(NULL, (LONG)init_count, (LONG)max_count, NULL);
}

bool release_semaphore(semaphore_handle handle, s32 count, s32* prev_count)
{
    return ReleaseSemaphore(handle, count, (LPLONG)prev_count);
}

bool wait_semaphore(semaphore_handle handle, u32 ms)
{
    const DWORD res = WaitForSingleObjectEx(handle, ms, FALSE);
    return win32_wait_res_check(handle, res);
}

mutex_handle create_mutex(bool signaled)
{
    return CreateMutex(NULL, (LONG)signaled, NULL);
}

bool release_mutex(mutex_handle handle)
{
    return ReleaseMutex(handle);
}

bool wait_mutex(mutex_handle handle, u32 ms)
{
    const DWORD res = WaitForSingleObjectEx(handle, ms, FALSE);
    return win32_wait_res_check(handle, res);
}

void init_critical_section(critical_section_handle handle, u32 spin_count)
{
    if (spin_count > 0)
        InitializeCriticalSectionAndSpinCount((LPCRITICAL_SECTION)handle, spin_count);
    else
        InitializeCriticalSection((LPCRITICAL_SECTION)handle);
}

void enter_critical_section(critical_section_handle handle)
{
    EnterCriticalSection((LPCRITICAL_SECTION)handle);
}

bool try_enter_critical_section(critical_section_handle handle)
{
    return TryEnterCriticalSection((LPCRITICAL_SECTION)handle);
}

void leave_critical_section(critical_section_handle handle)
{
    LeaveCriticalSection((LPCRITICAL_SECTION)handle);
}

void delete_critical_section(critical_section_handle handle)
{
    DeleteCriticalSection((LPCRITICAL_SECTION)handle);
}

void read_barrier()
{
    _ReadBarrier();
}

void write_barrier()
{
    _WriteBarrier();
}

void memory_barrier()
{
    _ReadWriteBarrier();
}

void read_fence()
{
    _mm_lfence();
}

void write_fence()
{
    _mm_sfence();
}

void memory_fence()
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

s32 atomic_increment(volatile s32* dst)
{
    return InterlockedIncrement((volatile LONG*)dst);
}

s32 atomic_decrement(volatile s32* dst)
{
    return InterlockedDecrement((volatile LONG*)dst);
}
