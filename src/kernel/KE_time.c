
#include "KE_time.h"
#include <SDL/SDL.h>

static long time_began = 0;

void KE_time_reset()
{
	time_began += KE_time_get();
}

long KE_time_get()
{
	return SDL_GetTicks() - time_began;
}

