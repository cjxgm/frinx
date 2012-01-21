
#include "snd_manager.h"
#include <AL/alc.h>
#include <stdlib.h>

ALuint snd_source;

int SND_init()
{
	ALCdevice  * dev = alcOpenDevice(NULL);
	ALCcontext * ctx = alcCreateContext(dev, NULL);
	alcMakeContextCurrent(ctx);

	alGenSources(1, &snd_source);

	alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSource3f(snd_source, AL_POSITION, 0.0f, 0.0f, 0.0f);

	return 0;
}

void SND_destroy()
{
	alDeleteSources(1, &snd_source);
}

int SND_is_playing()
{
	ALint state;
	alGetSourcei(snd_source, AL_SOURCE_STATE, &state);
	return state == AL_PLAYING;
}

