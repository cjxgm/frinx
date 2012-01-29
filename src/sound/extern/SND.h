
#ifndef __SND_H__
#define __SND_H__

#include <SDL/SDL_mixer.h>

typedef Mix_Music SND_Music;

int SND_init();
void SND_destroy();
int SND_is_playing();

int SND_playmusic(SND_Music * mus);
void SND_freemusic(SND_Music * mus);

#endif

