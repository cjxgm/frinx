
#ifndef __PHYS_H__
#define __PHYS_H__

#include "OBJ.h"

// Stick Constraint
typedef struct PHYS_ConStick
{
	float * node[2];	// 2 vectors
	float   len;
}
PHYS_ConStick;

void PHYS_verlet_apply(float pos[3], float oldpos[3], float force[3]);
void PHYS_con_stick_apply(PHYS_ConStick * con);

void PHYS_collide(float pos[3], float oldpos[3], OBJ_Object * obj);
int  PHYS_collide_tri_seg(
	float t1[3], float t2[3], float t3[3],	// triangle
	float s1[3], float s2[3],				// segment
	float cp[3]);							// collision point
int  PHYS_collide_plane_seg(
	float n[3], float p[3],					// plane (a normal & a point)
	float s1[3], float s2[3],				// segment
	float cp[3]);							// collision point
float PHYS_classify_plane_point(
	float n[3], float p[3],					// plane (a normal & a point)
	float tp[3]);							// the point

#endif

