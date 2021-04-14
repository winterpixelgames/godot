#ifndef CLOCK_H
#define CLOCK_H

#include <stdint.h>

// Class is needed to instrument List.h because OS.h #inclues List.h template etc etc
class Clock {

public:
	static uint64_t get_ticks_usec();
};

#endif
