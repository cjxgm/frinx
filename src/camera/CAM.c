
#include "CAM.h"
#include "KE_math.h"
#include <math.h>
#include <GL/glu.h>

void CAM_apply(CAM_Camera * cam)
{
	float eye[3];
	vec_mul(eye, cam->forward, -cam->dist);
	vec_addv(eye, cam->target);
	// TODO: Apply camera collision detection
	gluLookAt(eye[0], eye[1], eye[2],
			  cam->target[0], cam->target[1], cam->target[2],
			  cam->up[0], cam->up[1], cam->up[2]);
}

void CAM_turny(CAM_Camera * cam, float a)
{
	float c = cos(a);
	float s = sin(a);
	float rot[3] = {
		cam->forward[0]*c + cam->forward[2]*s,
		cam->forward[1],
		cam->forward[0]*(-s) + cam->forward[2]*c,
	};
	vec_cpy(cam->forward, rot);
}

