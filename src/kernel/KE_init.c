
#include "SND.h"
#include "SND_ogg.h"
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>	// FIXME Move this to <windowmanager>
#include "VG.h"			// FIXME Move away this`.
#include "VG_fvz.h"		// FIXME Move away this | to renderer
#include "KE_math.h"	// FIXME Move away this |
#include "KE_time.h"	// FIXME Move away this/

static VecGraph * vg;

void KE_init()
{
	SND_ogg_play("res/sound/logo");
	vg = VG_fvz_load("res/vecgraph/logo");
	KE_time_reset();
}

void KE_idle()
{
	// when playing done, exit.
	static int play_began = 0;
	if (SND_is_playing()) {
		if (!play_began) play_began = 1;
	}
	else if (play_began) exit(0);

	// render
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// logo animation
	glPushMatrix();
	glTranslatef(160, -120, 0);
	glColor3f(1.0f, 1.0f, 0.0f);
	long t = KE_time_get();
	if (t < 1000)
		VG_draw(vg, lirp(t, 0, 1000, 0, 0.8),
					lirp(t, 0, 1000, 0.2, 1), 0.05f, GL_LINE_STRIP);
	else if (t < 2000)
		VG_draw(vg, lirp(t, 1000, 2000, 0.9, 0),
					lirp(t, 1000, 2000, 1, 0.1), 0.01f, GL_LINE_STRIP);
	else if (t < 3000) {
		glLineWidth(1);
		VG_draw(vg, 0.0f, lirp(t, 2000, 3000, 0, 1), 0.01f, GL_LINE_STRIP);
		glColor4f(1.0f, 0.8f, 0.0f, lirp(t, 2000, 3000, 0, 1));
		glLineWidth(lirp(t, 2000, 3000, 1, 5));
		VG_draw(vg, lirp(t, 2000, 3000, 1, 0), 1.0f, 0.01f, GL_LINE_STRIP);
	}
	else if (t < 6000){
		glColor3f(1.0f, 0.8f, 0.0f);
		glLineWidth(lirp(t, 3000, 6000, 5, 1));
		VG_draw(vg, 0.0f, 1.0f, 0.01f, GL_LINE_STRIP);
	}
	else if (t < 8000){
		glLineWidth(1);
		glColor3f(1.0f, 0.8f, 0.0f);
		VG_draw(vg, 0.0f, 1.0f, 0.005f, GL_LINE_STRIP);
	}
	else if (t < 10000){
		glLineWidth(1);
		glColor4f(1.0f, 0.8f, 0.0f, lirp(t, 8000, 10000, 1, 0));
		VG_draw(vg, 0.0f, 1.0f, 0.005f, GL_LINE_STRIP);
	}
	glPopMatrix();

	glutSwapBuffers();
}

