#pragma once

// Time api use milliseconds by default.

#define SEC(ms)     (ms / 1000)
#define MIN(ms)     (SEC(ms) / 60)
#define HOUR(ms)    (MIN(ms) / 60)

u64 time_curr();		// current time
u64 time_sys_boot();	// time since system boot

u64 hp_counter();		// high precision counter
u64 hp_frequency();		// high precision frequency
