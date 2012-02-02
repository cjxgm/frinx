
#ifndef __PHYS_H__
#define __PHYS_H__


// Stick Constraint
typedef struct PHYS_ConStick
{
	float * node[2];	// 2 vectors
	float   len;
}
PHYS_ConStick;

void PHYS_verlet_apply(float pos[3], float oldpos[3], float force[3]);
void PHYS_con_stick_apply(PHYS_ConStick * con);

#endif

