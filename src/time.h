#pragma once

// Time api use milliseconds by default.

#define SEC(ms)     (ms / 1000)
#define MIN(ms)     (SEC(ms) / 60)
#define HOUR(ms)    (MIN(ms) / 60)

u64 tmcurr();
u64 tmsysboot();

u64 hpcounter();
u64 hpfrequency();

inline u64 timerstart()
{
    return tmcurr();
}

inline u64 timerstop(u64 start)
{
    return tmcurr() - start;
}
