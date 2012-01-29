
#include "SND_ogg.h"

SND_Music * SND_ogg_load(const char * file)
{
	return Mix_LoadMUS(file);
}

