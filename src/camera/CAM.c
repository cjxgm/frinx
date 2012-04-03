
#include "CAM.h"
#include "KE_math.h"
#include <math.h>
#include <GL/glu.h>

static float m[16];
static float rx=0, ry=0, rz=0;
float CAM_target[3] = {20, 3, 0};
float CAM_forward[3] = {0, 0, -1};
float CAM_up[3] = {0, 1, 0};
float CAM_dist = 2;

void CAM_apply()
{
	float eye[3];
	vec_mul(eye, CAM_forward, -CAM_dist);
	vec_addv(eye, CAM_target);
	// TODO: Apply camera collision detection
	gluLookAt(eye[0], eye[1], eye[2],
			  CAM_target[0], CAM_target[1], CAM_target[2],
			  CAM_up[0], CAM_up[1], CAM_up[2]);
}

void CAM_rotate(float ax, float ay, float az)
{
	rx += ax;
	ry += ay;
	rz += az;

	if (rx < -89) rx = -89;
	if (rx >  89) rx =  89;

	glPushMatrix();
	glLoadIdentity();
	glRotatef(rz, 0, 0, 1);
	glRotatef(ry, 0, 1, 0);
	glRotatef(rx, 1, 0, 0);
	glGetFloatv(GL_MODELVIEW_MATRIX, m);
	vec_cpy(CAM_up, &m[4]);
	vec_cpy(CAM_forward, &m[8]);
	glPopMatrix();
}

