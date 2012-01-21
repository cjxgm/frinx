

#include "snd_manager.h"
#include <vorbis/vorbisfile.h>

#define BUFFER_SIZE     1024*4       // 4 KB buffer
#define BUFFER_CNT		4

static ALuint buffer[BUFFER_CNT];

// Deffering from ov_read, it will make sure that the buffer is full
// or it will continue reading till it's full, unless for the last bits.
static int ov_read2(OggVorbis_File * ogg, char * buf, int buf_size)
{
	int bs;
	int cnt = 0;
	while (buf_size - cnt > 0) {
		int t = ov_read(ogg, &buf[cnt], buf_size - cnt, 0, 2, 1, &bs);
		if (t == 0) break;
		cnt += t;
	}
	return cnt;
}

int SND_ogg_play(const char * file)
{
	ALint   state;
	ALenum  format;
	ALsizei freq;
	int		cnt;
	char	buf[BUFFER_SIZE];
	FILE  * fp;

	if (!(fp = fopen(file, "r")))
		return -1;

	vorbis_info		  * info;
	OggVorbis_File		ogg;

	if (ov_open(fp, &ogg, NULL, 0))
		return -2;

	info = ov_info(&ogg, -1);
	freq = info->rate;
	if (info->channels == 1)
		format = AL_FORMAT_MONO16;
	else format = AL_FORMAT_STEREO16;

	alGenBuffers(BUFFER_CNT, buffer);

	int i;
	for (i=0; i<BUFFER_CNT; i++) {
		cnt = ov_read2(&ogg, buf, BUFFER_SIZE);
		if (cnt > 0) alBufferData(buffer[i], format, buf, cnt, freq);
	}

	alSourceQueueBuffers(snd_source, BUFFER_CNT, buffer);
	alSourcePlay(snd_source);

	while (1) {
		ALuint b;

		alGetSourcei(snd_source, AL_BUFFERS_PROCESSED, &state);
		if (state <= 0) continue;

		while (state--) {
			alSourceUnqueueBuffers(snd_source, 1, &b);
			cnt = ov_read2(&ogg, buf, BUFFER_SIZE);
			if (cnt > 0) alBufferData(b, format, buf, cnt, freq);
			else goto _end;
			alSourceQueueBuffers(snd_source, 1, &b);
		}

		alGetSourcei(snd_source, AL_SOURCE_STATE, &state);
		if(state != AL_PLAYING)
			alSourcePlay(snd_source);
	}

_end:
	ov_clear(&ogg);		// no need for fclose(fp)
	alDeleteBuffers(BUFFER_CNT, buffer);
	return 0;
}

