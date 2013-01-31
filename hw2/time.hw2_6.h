
	#ifndef __RPi_sys_time__
	#define __RPi_sys_time__

	// Get the system time, from the RPi's free running clock.
	// The value increments by 1 every microsecond.

	uint64_t getSystemTime();

	#endif