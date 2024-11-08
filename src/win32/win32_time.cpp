#include "pch.h"
#include "time.h"

u64 tmcurr()
{
    return hpcounter() * 1000ull / hpfrequency();
}

u64 tmsysboot()
{
    return GetTickCount64();
}

u64 hpcounter()
{
    LARGE_INTEGER counter;
    const BOOL res = QueryPerformanceCounter(&counter);
    ASSERT(res);
    return counter.QuadPart;
}

u64 hpfrequency()
{
    static u64 frequency64 = 0;

    if (frequency64 == 0)
    {
        LARGE_INTEGER frequency;
        const BOOL res = QueryPerformanceFrequency(&frequency);
        ASSERT(res);
        frequency64 = frequency.QuadPart;
    }
    
    return frequency64;
}
