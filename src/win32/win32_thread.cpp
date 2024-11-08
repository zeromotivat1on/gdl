#include "pch.h"
#include "thread.h"
#include <intrin.h>

#define INVALID_THREAD_RESULT ((DWORD)-1)

static DWORD win32_thcreatetype(s32 type)
{
    switch(type)
    {
        case THREAD_SUSPENDED: return CREATE_SUSPENDED;
        case THREAD_IMMEDIATE:
        default: return 0;
    }
}

u64 thcurrid()
{
    return GetCurrentThreadId();
}

void thsleep(u32 ms)
{
    Sleep(ms);
}

bool thactive(thhandle handle)
{
    DWORD exitCode;
    GetExitCodeThread(handle, &exitCode);
    return exitCode == STILL_ACTIVE;
}

thhandle thcreate(s32 type, thentry entry, void* userdata)
{
    return CreateThread(0, 0, (LPTHREAD_START_ROUTINE)entry, userdata, win32_thcreatetype(type), NULL);
}

void thresume(thhandle handle)
{
    const DWORD res = ResumeThread(handle);
    ASSERT(res != INVALID_THREAD_RESULT);
}

void thsuspend(thhandle handle)
{
    const DWORD res = SuspendThread(handle);
    ASSERT(res != INVALID_THREAD_RESULT);
}

void thterminate(thhandle handle)
{
    DWORD exitCode;
    GetExitCodeThread(handle, &exitCode);
    const BOOL res = TerminateThread(handle, exitCode);
    ASSERT(res);
}

smhandle smcreate(bool signaled)
{
    return CreateSemaphore(nullptr, (LONG)signaled, 1, nullptr);
}

void smrelease(smhandle handle)
{
    LONG prevCount;
    ReleaseSemaphore(handle, 1, &prevCount);
}

void smwait(smhandle handle, u32 ms)
{
    WaitForSingleObjectEx(handle, ms, FALSE);
}

void rbarrier()
{
    _ReadBarrier();
}

void wbarrier()
{
    _WriteBarrier();
}

void mbarrier()
{
    _ReadWriteBarrier();
}

void rfence()
{
    _mm_lfence();
}

void wfence()
{
    _mm_sfence();
}

void mfence()
{
    _mm_mfence();
}

s32 atmswap(volatile s32* dst, s32 val)
{
    return InterlockedExchange((volatile LONG*)dst, val);
}

s32 atmcmpswap(volatile s32* dst, s32 val, s32 cmp)
{
    return InterlockedCompareExchange((volatile LONG*)dst, val, cmp);
}

void* atmcmpswap(volatile void** dst, void* val, void* cmp)
{
    return InterlockedCompareExchangePointer((volatile LPVOID*)dst, val, cmp);
}

s32 atmadd(volatile s32* dst, s32 val)
{
    return InterlockedAdd((volatile LONG*)dst, val);
}

s32 atminc(volatile s32* dst)
{
    return InterlockedIncrement((volatile LONG*)dst);
}

s32 atmdec(volatile s32* dst)
{
    return InterlockedDecrement((volatile LONG*)dst);
}
