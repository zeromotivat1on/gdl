#include "pch.h"
#include "time.h"

u64 time_curr()
{
    return hp_counter() * 1000ull / hp_frequency();
}

u64 time_sys_boot()
{
    return GetTickCount64();
}

u64 hp_counter()
{
    LARGE_INTEGER counter;
    const BOOL res = QueryPerformanceCounter(&counter);
    ASSERT(res);
    return counter.QuadPart;
}

u64 hp_frequency()
{
    static u64 frequency64 = 0;

    if (frequency64 == 0)
    {
        LARGE_INTEGER frequency;
        const BOOL res = QueryPerformanceFrequency(&frequency);
        ASSERT(res);
        frequency64 = (u64)frequency.QuadPart;
    }
    
    return frequency64;
}
