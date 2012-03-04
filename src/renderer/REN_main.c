
#include "REN_main.h"
#include "REN_staff.h"
#include "FX_sparti.h"
#include "KE_time.h"
#include "KE.h"
#include "WM.h"
#include "MAN_res.h"
#include "CAM.h"
#include "PHYS.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>

static FX_SParti  * sp;
static OBJ_Object * obj;
static SND_Music  * music;
static CAM_Camera   cam = {
	{ 0, 0, 0 },	// target
	{ 0, 0, -1 },	// forward
	{ 0, 1, 0 },	// up
	2				// dist
};

static void setup_3d()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)WM_winw / (float)WM_winh, 1, 100);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);

	/* lighting */ {
		float light_pos[] = { -1, -1, 0, 0 };
		float white_light[] = { 3, 3, 3, 1 };
		//float ambient[] = { 1, 1, 1, 1 };

		glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
		glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
		//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
		//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

		glEnable(GL_LIGHT0);
	}
	/* lighting */ {
		float light_pos[] = { 1, 1, 1, 0 };
		float white_light[] = { 1, 1, 1, 1 };

		glLightfv(GL_LIGHT1, GL_POSITION, light_pos);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, white_light);
		glLightfv(GL_LIGHT1, GL_SPECULAR, white_light);

		glEnable(GL_LIGHT1);
	}
}

void REN_main_init()
{
	sp = FX_sparti_new(1000);
	float v[] = {0, 10, 5};
	float p[] = {0, 0, -10};
	FX_sparti_init(sp, v, v, p, 2000, 1000, 10, 10, 0, 1000);

	obj = MAN_res_loadobj("city");
	music = MAN_res_loadsnd("intro");

	setup_3d();
	KE_time_reset();
}

static void proc_key()
{
	static int wait_release = 0;
	if (WM_key['\e'])
		wait_release = 1;
	else if (wait_release)
		KE_SET_RENDERER(staff);

	if (WM_key['w']) {
		cam.target[0] += cam.forward[0] * 3*KE_spf;
		/* DO NOT MOVE UP */
		cam.target[2] += cam.forward[2] * 3*KE_spf;
	}
	if (WM_key['s']) {
		cam.target[0] -= cam.forward[0] * 3*KE_spf;
		/* DO NOT MOVE DOWN */
		cam.target[2] -= cam.forward[2] * 3*KE_spf;
	}
	if (WM_key['a']) {
		float right[3];
		vec_unit_normal(right, cam.forward, cam.up);
		cam.target[0] -= right[0] * 3*KE_spf;
		/* DO NOT MOVE DOWN */
		cam.target[2] -= right[2] * 3*KE_spf;
	}
	if (WM_key['d']) {
		float right[3];
		vec_unit_normal(right, cam.forward, cam.up);
		cam.target[0] += right[0] * 3*KE_spf;
		/* DO NOT MOVE DOWN */
		cam.target[2] += right[2] * 3*KE_spf;
	}
	if (WM_key[WM_KEY_LEFT])
		CAM_turny(&cam, +2*KE_spf);
	if (WM_key[WM_KEY_RIGHT])
		CAM_turny(&cam, -2*KE_spf);
	if (WM_key[WM_KEY_UP]) {
		cam.dist -= 3*KE_spf;
		if (cam.dist < 0.1) cam.dist = 0.1;
	}
	if (WM_key[WM_KEY_DOWN])
		cam.dist += 3*KE_spf;
}

void REN_main()
{
	proc_key();
	if (!SND_is_playing())
		SND_playmusic(music);

	glPushMatrix(); {
		CAM_apply(&cam);

		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		glPointSize(10);
		float color[] = {1.0, 0.8, 0.0};
		FX_sparti_draw(sp, color);
		FX_sparti_calc(sp);

		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		OBJ_draw(obj);
	} glPopMatrix();
}

