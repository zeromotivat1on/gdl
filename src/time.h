#pragma once

// Time api use milliseconds by default.

#define SEC(ms)     (ms / 1000)
#define MIN(ms)     (SEC(ms) / 60)
#define HOUR(ms)    (MIN(ms) / 60)

u64 tmcurr();       // current time
u64 tmsysboot();    // time since system boot

u64 hpcounter();    // high precision counter
u64 hpfrequency();  // high precision frequency
