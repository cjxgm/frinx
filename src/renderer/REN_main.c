
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

//// PHYSICS
static OBJ_Object      mesh;
static PHYS_ConStick * cons;
static int			   cons_cnt;
static OBJ_Coord     * oldco;
static float           target[3];

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

///////// INIT PHYSICS ////////
#define VS		30
#define CO(X,Z)	((Z)*VS+(X))

	mesh.vs_cnt = VS*VS;
	mesh.fs_cnt = 2*(VS-1)*(VS-1);
	cons_cnt    = 2*VS*(VS-1);
	mesh.vs = malloc(sizeof(OBJ_Coord)*mesh.vs_cnt);
	oldco   = malloc(sizeof(OBJ_Coord)*mesh.vs_cnt);
	mesh.fs = malloc(sizeof(OBJ_Face )*mesh.fs_cnt);
	mesh.ns = malloc(sizeof(OBJ_Coord)*mesh.fs_cnt);
	cons    = malloc(sizeof(PHYS_ConStick)*cons_cnt);

	float sss = 1.5f / VS;
	int x, z;
	int fid = 0, cid = 0;	// face id; cons id
	for (z=0; z<VS; z++)
		for (x=0; x<VS; x++) {
			// generate vertex
			mesh.vs[CO(x, z)].co[0] = x*sss;
			mesh.vs[CO(x, z)].co[1] = 1;
			mesh.vs[CO(x, z)].co[2] = z*sss;
			vec_cpy(oldco[CO(x, z)].co, mesh.vs[CO(x, z)].co);
			// generate face
			if (z < VS-1 && x < VS-1) {
				mesh.fs[fid].id[0] = CO(x, z);
				mesh.fs[fid].id[1] = CO(x+1, z+1);
				mesh.fs[fid].id[2] = CO(x+1, z);
				fid++;
				mesh.fs[fid].id[0] = CO(x, z);
				mesh.fs[fid].id[1] = CO(x, z+1);
				mesh.fs[fid].id[2] = CO(x+1, z+1);
				fid++;
			}
			// generate cons
			if (x < VS-1) {
				cons[cid].node[0] = mesh.vs[CO(x, z)].co;
				cons[cid].node[1] = mesh.vs[CO(x+1, z)].co;
				cons[cid].len = sss;
				cid++;
			}
			if (z < VS-1) {
				cons[cid].node[0] = mesh.vs[CO(x, z)].co;
				cons[cid].node[1] = mesh.vs[CO(x, z+1)].co;
				cons[cid].len = sss;
				cid++;
			}
		}
/////// INIT PHYSICS END //////

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
	
	if (WM_key[' '])
		vec_cpy(target, cam.target);
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

///////// PHYSICS ////////
		int i, j;
#define PREC	3
//// APPLY
		float force[3] = {0, -5, 0};
		for (i=0; i<mesh.vs_cnt; i++)
			PHYS_verlet_apply(mesh.vs[i].co, oldco[i].co, force);

		for (j=0; j<PREC; j++) {
			for (i=0; i<mesh.vs_cnt; i++) {
				/*
				if (mesh.vs[i].co[1] < -0.7)
					mesh.vs[i].co[1] = -0.7;
				*/
				PHYS_collide(mesh.vs[i].co, oldco[i].co, obj);
			}
			for (i=0; i<cons_cnt; i++)
				PHYS_con_stick_apply(&cons[i]);
			mesh.vs[mesh.vs_cnt>>1].co[1] = 0.6;
			vec_cpy(mesh.vs[0].co, target);
			vec_cpy(mesh.vs[mesh.vs_cnt-1].co, cam.target);
		}
//// DRAW
		glBegin(GL_TRIANGLES);
		for (i=0; i<mesh.fs_cnt; i++) {
			// normal
			float v[3][3];
			vec_sub(v[0], mesh.vs[mesh.fs[i].id[1]].co,
						  mesh.vs[mesh.fs[i].id[0]].co);
			vec_sub(v[1], mesh.vs[mesh.fs[i].id[2]].co,
						  mesh.vs[mesh.fs[i].id[0]].co);

			vec_unit_normal(v[2], v[0], v[1]);
			glNormal3fv(v[2]);
			glVertex3fv(mesh.vs[mesh.fs[i].id[0]].co);
			glVertex3fv(mesh.vs[mesh.fs[i].id[1]].co);
			glVertex3fv(mesh.vs[mesh.fs[i].id[2]].co);

			vec_unit_normal(v[2], v[1], v[0]);
			glNormal3fv(v[2]);
			glVertex3fv(mesh.vs[mesh.fs[i].id[2]].co);
			glVertex3fv(mesh.vs[mesh.fs[i].id[1]].co);
			glVertex3fv(mesh.vs[mesh.fs[i].id[0]].co);
		}
		glEnd();
/////// PHYSICS END //////

		glEnable(GL_TEXTURE_2D);
		OBJ_draw(obj);
	} glPopMatrix();
}

