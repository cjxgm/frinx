
#include "SND.h"
#include "SND_ogg.h"
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>	// FIXME Move this to <windowmanager>

void KE_init()
{
	SND_ogg_play("res/sound/logo");
}

void KE_idle()
{
	static int play_began = 0;

	if (SND_is_playing()) {
		if (!play_began) play_began = 1;
	}
	else if (play_began) exit(0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutSwapBuffers();
}

