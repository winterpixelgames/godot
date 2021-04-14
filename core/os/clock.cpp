#include "clock.h"
#include "os.h"

uint64_t Clock::get_ticks_usec() {
	if (OS::get_singleton()) {
		return OS::get_singleton()->get_ticks_usec();
	}
	return 0;
}
