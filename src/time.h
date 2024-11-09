#pragma once

// Time api use milliseconds by default.

#define SEC(ms)     (ms / 1000)
#define MIN(ms)     (SEC(ms) / 60)
#define HOUR(ms)    (MIN(ms) / 60)

u64 timecurr();
u64 timesysboot();

u64 hpcounter();
u64 hpfrequency();

inline u64 timerstart()
{
    return timecurr();
}

inline u64 timerstop(u64 start)
{
    return timecurr() - start;
}
