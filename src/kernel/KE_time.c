
#include "KE_time.h"
#include <time.h>

static long time_began = 0;

void KE_time_reset()
{
	time_began += KE_time_get();
}

long KE_time_get()
{
	return clock() * 1000 / CLOCKS_PER_SEC - time_began;
}

