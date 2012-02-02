
#include "REN_main.h"
#include "FX_sparti.h"
#include "KE_time.h"
#include "KE.h"
#include "WM.h"
#include "MAN_res.h"
#include <GL/gl.h>
#include <GL/glu.h>

static FX_SParti  * sp;
static OBJ_Object * obj;
static SND_Music  * music;
static float a = 0.0f;

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
	float v[] = {0, 0, 0};
	float p[] = {0, 0, -20};
	FX_sparti_init(sp, v, v, p, 2000, 10, 10, 0, 1000);

	obj = MAN_res_loadobj("city");
	music = MAN_res_loadsnd("intro");

	setup_3d();
	glTranslatef(0, 0, -4);
	SND_playmusic(music);
	KE_time_reset();
}

void REN_main()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glPointSize(10);
	float color[] = {1.0, 0.8, 0.0};
	FX_sparti_draw(sp, color);
	FX_sparti_calc(sp);

	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix(); {
		glRotatef(a += KE_spf * 30, 0, 1, 0);
		OBJ_draw(obj);
	} glPopMatrix();
}

