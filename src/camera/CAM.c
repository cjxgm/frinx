
#include "CAM.h"
#include "KE_math.h"
#include "PHYS.h"
#include <math.h>
#include <GL/glu.h>

static float m[16];
float CAM_rot[3] = {0, 0, 0};
float CAM_target[3] = {20, 0.8, 0};
float CAM_forward[3] = {0, 0, -1};
float CAM_up[3] = {0, 1, 0};
float CAM_dist = 2;

void CAM_apply()
{
	float eye[3];
	vec_mul(eye, CAM_forward, -CAM_dist);
	vec_addv(eye, CAM_target);
	// TODO: camera collision
	gluLookAt(eye[0], eye[1], eye[2],
			  CAM_target[0], CAM_target[1], CAM_target[2],
			  CAM_up[0], CAM_up[1], CAM_up[2]);
}

void CAM_rotate(float ax, float ay, float az)
{
	CAM_rot[0] += ax;
	CAM_rot[1] += ay;
	CAM_rot[2] += az;

	if (CAM_rot[0] < -89) CAM_rot[0] = -89;
	if (CAM_rot[0] >  89) CAM_rot[0] =  89;

	glPushMatrix();
	glLoadIdentity();
	glRotatef(CAM_rot[2], 0, 0, 1);
	glRotatef(CAM_rot[1], 0, 1, 0);
	glRotatef(CAM_rot[0], 1, 0, 0);
	glGetFloatv(GL_MODELVIEW_MATRIX, m);
	vec_cpy(CAM_up, &m[4]);
	vec_cpy(CAM_forward, &m[8]);
	glPopMatrix();
}

