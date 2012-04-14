
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
static OBJ_Object * player;
static OBJ_Object * player2;
static SND_Music  * music;
static int player_is_doing = 0;

static void setup_3d()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,
		(float)WM_winw / (WM_naked3d ? 2.0 : 1.0f) / (float)WM_winh,
		1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

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
	obj = MAN_res_loadobj("city");
	player = MAN_res_loadobj("player1");
	player2 = MAN_res_loadobj("player2");
	music = MAN_res_loadsnd("intro");

	// fix player's position
	vec_cpy(player->pos, CAM_target);
	vec_cpy(player2->pos, CAM_target);
	player2->pos[1] = player->pos[1] = 0.38;
	player2->pos[2] += 2;
	player2->pos[0] += 1;

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

	static int wait_release_f = 0;
	if (WM_key['f'])
		wait_release_f = 1;
	else if (wait_release_f) {
		wait_release_f = 0;
		if (player_is_doing) {
			OBJ_stopanim(player);
			OBJ_stopanim(player2);
			player_is_doing = 0;
		}
		else {
			float t[3];
			vec_sub(t, player->pos, player2->pos);
			if (vec_mod(t) < 0.5) {
				OBJ_playanim(player, "fuck");
				OBJ_playanim(player2, "fucked");
				vec_cpy(player->pos, player2->pos);
				glPushMatrix(); {	// get forward vector
					glLoadIdentity();
					glRotatef(player->rot[2], 0, 0, 1);
					glRotatef(player->rot[1], 0, 1, 0);
					float m[16];
					glGetFloatv(GL_MODELVIEW_MATRIX, m);
					vec_cpy(t, &m[8]);
				} glPopMatrix();
				vec_mulv(t, 0.1);
				vec_subv(player->pos, t);
				// apply back to the camera
				vec_cpy(CAM_target, player->pos);
				// make player2 face at player
				player2->rot[1] = 180 + player->rot[1];
				player_is_doing = 1;
			}
		}
	}

	if (!player_is_doing) {
		if (WM_key['w'] || WM_key['s'] || WM_key['a'] || WM_key['d']) {
			float fwd[3] = {CAM_forward[0], 0, CAM_forward[2]};
			vec_normv(fwd);
			float newpos[3];
			vec_cpy(newpos, CAM_target);

			if (WM_key['w']) {
				newpos[0] += fwd[0] * 2*KE_spf;
				/* DO NOT MOVE UP */
				newpos[2] += fwd[2] * 2*KE_spf;
				PHYS_collide(newpos, CAM_target, obj);
				vec_cpy(CAM_target, newpos);
				vec_cpy(player->rot, CAM_rot);
				if (!OBJ_isanim(player, "walk"))
					OBJ_playanim(player, "walk");
			}

			if (WM_key['s']) {
				newpos[0] -= fwd[0] * 2*KE_spf;
				/* DO NOT MOVE DOWN */
				newpos[2] -= fwd[2] * 2*KE_spf;
				PHYS_collide(newpos, CAM_target, obj);
				vec_cpy(CAM_target, newpos);
				vec_cpy(player->rot, CAM_rot);
				player->rot[1] -= 180;
				if (!OBJ_isanim(player, "walk"))
					OBJ_playanim(player, "walk");
			}

			if (WM_key['a']) {
				float right[3];
				vec_unit_normal(right, CAM_forward, CAM_up);
				newpos[0] -= right[0] * 2*KE_spf;
				/* DO NOT MOVE DOWN */
				newpos[2] -= right[2] * 2*KE_spf;
				PHYS_collide(newpos, CAM_target, obj);
				vec_cpy(CAM_target, newpos);
				vec_cpy(player->rot, CAM_rot);
				player->rot[1] += 90;
				if (!OBJ_isanim(player, "walk"))
					OBJ_playanim(player, "walk");
			}

			if (WM_key['d']) {
				float right[3];
				vec_unit_normal(right, CAM_forward, CAM_up);
				newpos[0] += right[0] * 2*KE_spf;
				/* DO NOT MOVE DOWN */
				newpos[2] += right[2] * 2*KE_spf;
				PHYS_collide(newpos, CAM_target, obj);
				vec_cpy(CAM_target, newpos);
				vec_cpy(player->rot, CAM_rot);
				player->rot[1] -= 90;
				if (!OBJ_isanim(player, "walk"))
					OBJ_playanim(player, "walk");
			}

			vec_cpy(player->pos, CAM_target);
			player->pos[1] = 0.38;
		}
		else OBJ_stopanim(player);
	}

	/* mouse */{
		int x, y;
		WM_get_relative_mouse_pos(&x, &y);
		CAM_rotate(0.2f*y, -0.2f*x, 0);
	}
}

static void draw()
{
	glPushMatrix(); {
		CAM_apply();

		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		OBJ_draw(obj);
		glPushMatrix(); {
			glTranslatef(player->pos[0], player->pos[1], player->pos[2]);
			glRotatef(player->rot[2], 0, 0, 1);
			glRotatef(player->rot[1], 0, 1, 0);
			glScalef(0.08, 0.08, 0.08);
			OBJ_draw(player);
			// shadow
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_LIGHTING);
			float a = 0;
			glColor4f(0, 0, 0, 0.2);
			glBegin(GL_POLYGON);
			for (a=0; a>-2*PI; a-=0.1)
				glVertex3f(2*cos(a), -4.7, 2*sin(a));
			glEnd();
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_LIGHTING);
		} glPopMatrix();
		glPushMatrix(); {
			glTranslatef(player2->pos[0], player2->pos[1], player2->pos[2]);
			glRotatef(player2->rot[2], 0, 0, 1);
			glRotatef(player2->rot[1], 0, 1, 0);
			glScalef(0.08, 0.08, 0.08);
			OBJ_draw(player2);
			// shadow
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_LIGHTING);
			float a = 0;
			glColor4f(0, 0, 0, 0.2);
			glBegin(GL_POLYGON);
			for (a=0; a>-2*PI; a-=0.1)
				glVertex3f(2*cos(a), -4.71, 2*sin(a));
			glEnd();
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_LIGHTING);
		} glPopMatrix();
	} glPopMatrix();
}

void REN_main()
{
	proc_key();
	if (!SND_is_playing())
		SND_playmusic(music);

	if (WM_naked3d) {
		glPushMatrix(); {
			glViewport(0, 0, WM_winw/2, WM_winh);
			glTranslatef(+0.03, 0, 0);
			draw();
			glViewport(WM_winw/2, 0, WM_winw/2, WM_winh);
			glTranslatef(-0.06, 0, 0);
			draw();
		} glPopMatrix();
	}
	else draw();
}

