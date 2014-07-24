
#include "PHYS.h"
#include "KE_math.h"
#include <math.h>
#include <stdio.h>

void PHYS_collide(float pos[3], float oldpos[3], OBJ_Object * obj)
{
	float cp[3];
	int i;

	OBJ_stopanim(obj);
	OBJ_Coord * vs = obj->as[obj->anim_playing].frames[0].vs;

	for (i=0; i<obj->fs_cnt; i++) {
		if (PHYS_collide_tri_seg(vs[obj->fs[i].id[0]].co,
								 vs[obj->fs[i].id[1]].co,
								 vs[obj->fs[i].id[2]].co,
								 pos, oldpos, cp)) {
			vec_cpy(pos, cp);
			vec_cpy(oldpos, cp);
		}
	}
}

int  PHYS_collide_tri_seg(
	float t1[3], float t2[3], float t3[3],	// triangle
	float s1[3], float s2[3],				// segment
	float cp[3])							// collision point
{
	float e[3][3];
	float n[3];
	vec_sub(e[0], t2, t1);
	vec_sub(e[1], t3, t2);
	vec_unit_normal(n, e[0], e[1]);
	if (!PHYS_collide_plane_seg(n, t1, s1, s2, cp))
		return 0;

	vec_sub(e[2], t1, t3);
	float en[3];

	vec_unit_normal(en, n, e[0]);
	if (PHYS_classify_plane_point(en, t1, cp) < 0)
		return 0;

	vec_unit_normal(en, n, e[1]);
	if (PHYS_classify_plane_point(en, t2, cp) < 0)
		return 0;

	vec_unit_normal(en, n, e[2]);
	if (PHYS_classify_plane_point(en, t3, cp) < 0)
		return 0;

	return 1;
}

int  PHYS_collide_plane_seg(
	float n[3], float p[3],					// plane (a normal & a point)
	float s1[3], float s2[3],				// segment
	float cp[3])							// collision point
{
	float a = PHYS_classify_plane_point(n, p, s1);
	float b = PHYS_classify_plane_point(n, p, s2);

	if (a*b >= 0) return 0;

	vec_sub(cp, s2, s1);
	vec_mulv(cp, a / (a-b) + 0.005);
	vec_addv(cp, s1);

	return 1;
}

float PHYS_classify_plane_point(
	float n[3], float p[3],					// plane (a normal & a point)
	float tp[3])							// the point
{
	float a = vec_dot(n, tp) - vec_dot(n, p);
	if (a < 0.1f && a > 0.1f) return 0.0f;
	return a;
}

