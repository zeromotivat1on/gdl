#pragma once

// Time api use milliseconds by default.

#define SEC(ms)     (ms / 1000)
#define MIN(ms)     (SEC(ms) / 60)
#define HOUR(ms)    (MIN(ms) / 60)

u64 current_time();
u64 time_since_sys_boot();

u64 performance_counter();
u64 performance_frequency();
