
#include "SND.h"
#include <SDL/SDL_mixer.h>

int SND_init()
{
	return Mix_OpenAudio(48000, AUDIO_S16LSB, 2, 4096);
}

void SND_destroy()
{
	Mix_CloseAudio();
}

int SND_is_playing()
{
	return Mix_PlayingMusic();
}

int SND_playmusic(SND_Music * mus)
{
	if (Mix_PlayMusic(mus, 0) < 0) return -1;
	return 0;
}

void SND_freemusic(SND_Music * mus)
{
	Mix_FreeMusic(mus);
}

