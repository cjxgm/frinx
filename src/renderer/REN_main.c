
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

static OBJ_Object * obj;
static SND_Music  * music;

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
	obj = MAN_res_loadobj("anim");
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

	float fwd[3] = {CAM_forward[0], 0, CAM_forward[2]};
	vec_normv(fwd);
	if (WM_key['w']) {
		CAM_target[0] += fwd[0] * 3*KE_spf;
		/* DO NOT MOVE UP */
		CAM_target[2] += fwd[2] * 3*KE_spf;
	}
	if (WM_key['s']) {
		CAM_target[0] -= fwd[0] * 3*KE_spf;
		/* DO NOT MOVE DOWN */
		CAM_target[2] -= fwd[2] * 3*KE_spf;
	}
	if (WM_key['a']) {
		float right[3];
		vec_unit_normal(right, CAM_forward, CAM_up);
		CAM_target[0] -= right[0] * 3*KE_spf;
		/* DO NOT MOVE DOWN */
		CAM_target[2] -= right[2] * 3*KE_spf;
	}
	if (WM_key['d']) {
		float right[3];
		vec_unit_normal(right, CAM_forward, CAM_up);
		CAM_target[0] += right[0] * 3*KE_spf;
		/* DO NOT MOVE DOWN */
		CAM_target[2] += right[2] * 3*KE_spf;
	}
	if (WM_key[' '])
		OBJ_playanim(obj, "walk");

	/* mouse */{
		int x, y;
		WM_get_relative_mouse_pos(&x, &y);
		CAM_rotate(0.2f*y, -0.2f*x, 0);
	}
}

void REN_main()
{
	proc_key();
	if (!SND_is_playing())
		SND_playmusic(music);

	glPushMatrix(); {
		CAM_apply();

		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		OBJ_draw(obj);
	} glPopMatrix();
}

