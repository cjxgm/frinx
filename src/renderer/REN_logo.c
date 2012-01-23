
#include "REN_logo.h"
#include "REN_main.h"
#include "SND.h"
#include "SND_ogg.h"
#include "VG.h"
#include "VG_fvz.h"
#include "KE.h"
#include "KE_math.h"
#include "KE_time.h"
#include "FX_sparti.h"
#include <GL/gl.h>
#include <stdlib.h>

static VecGraph * vg;
static FX_SParti * sp;
static FX_SParti ** sps;
static int sps_len;

void REN_logo_init()
{
	vg = VG_fvz_load("res/vecgraph/logo");
	SND_ogg_play("res/sound/logo");
}

void REN_logo()
{
	static int state = 0;
	// when playing began, reset time;
	// when it ended, turn to main menu.
	static int play_began = 0;
	if (SND_is_playing()) {
		if (!play_began) {
			play_began = 1;
			KE_time_reset();
		}
	}
	else if (play_began) KE_SET_RENDERER(main);
	else return;

	// logo animation
	glPushMatrix();
	glTranslatef(160, 360, 0);
	glScalef(1, -1, 1);

	glColor3f(1.0f, 1.0f, 0.0f);
	long t = KE_time_get();
	if (t < 1000)
		VG_draw(vg, lirp(t, 0, 1000, 0, 0.8),
					lirp(t, 0, 1000, 0.2, 1), 0.01f, GL_POLYGON);
	else if (t < 2000)
		VG_draw(vg, lirp(t, 1000, 2000, 0.9, 0),
					lirp(t, 1000, 2000, 1, 0.1), 0.01f, GL_LINE_STRIP);
	else if (t < 3000) {
		if (state == 0) {
			state++;

			// init sp
			sp = FX_sparti_new(2000);
			float vzero[] = {0, 0, 0};
			float p[] = {160, 80, 0};
			FX_sparti_init(sp, vzero, vzero, p, 800, 2000, 500, 0, 0);
		}
		glLineWidth(1);
		VG_draw(vg, 0.0f, lirp(t, 2000, 3000, 0, 1), 0.01f, GL_LINE_STRIP);

		glPushMatrix();
		glColor4f(1.0f, 0.8f, 0.0f, lirp(t, 2000, 3000, 0, 1));
		glLineWidth(5);
		float a = lirp(t, 2000, 3000, 6, 1);
		glTranslatef(160, 120, 0);
		glScalef(a, a, 1);
		glTranslatef(-160, -120, 0);
		VG_draw(vg, 0.0f, 1.0f, 0.01f, GL_LINE_STRIP);
		glPopMatrix();

		// draw sp
		if (t >= 2200) {
			glPointSize(10);
			float color[] = {1.0, 0.8, 0.0};
			FX_sparti_draw(sp, color);
			FX_sparti_calc(sp);
		}
	}
	else if (t < 6000){
		glLineWidth(1);
		glColor3f(1.0f, 0.8f, 0.0f);
		VG_draw(vg, 0.0f, 1.0f, lirp(t, 3000, 6000, 0.01f, 0.005f),
														GL_LINE_STRIP);
		glLineWidth(5);
		glColor4f(1.0f, 0.8f, 0.0f, lirp(t, 3000, 6000, 1, 0));
		VG_draw(vg, 0.0f, 1.0f, 0.01f, GL_LINE_STRIP);
	}
	else if (t < 8000){
		glLineWidth(1);
		glColor3f(1.0f, 0.8f, 0.0f);
		VG_draw(vg, 0.0f, 1.0f, 0.005f, GL_LINE_STRIP);
	}
	else if (t < 9000){
		if (state == 1) {
			state++;

			// free sp
			free(sp);

			// init sps
			int i = 0;
			sps_len = link_length(&vg->eqts);
			sps = malloc(sizeof(void *) * sps_len);
			{ TRAVERSE(&vg->eqts, BezEqt3, eqt3) {
				sp = FX_sparti_new(50);
				float v[] = {0, -80, 0};
				float p[3];
				bez_eqt3_eval(eqt3, 0, p);
				FX_sparti_init(sp, v, v, p, 1800, 50, 20, 10, 100);
				sps[i++] = sp;
			}}
		}
		glLineWidth(1);
		glColor3f(1.0f, 0.8f, 0.0f);
		VG_draw(vg, lirp(t, 8000, 9000, 0.0f, 0.5f),
					lirp(t, 8000, 9000, 1.0f, 0.5f),
					0.005f, GL_LINE_STRIP);
	}
	// draw sps
	if (t > 8200 && t <= 10000) {
		int i;
		for (i=0; i<sps_len; i++) {
			glPointSize(10);
			float color[] = {1.0, 0.8, 0.0};
			FX_sparti_draw(sps[i], color);
			FX_sparti_calc(sps[i]);
		}
	}
	glPopMatrix();
}

