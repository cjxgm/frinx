
#include "PHYS.h"
#include "KE_math.h"
#include <math.h>
#include <stdio.h>

void PHYS_collide(float pos[3], float oldpos[3], OBJ_Object * obj)
{
	float cp[3];
	int i;

	for (i=0; i<obj->fs_cnt; i++) {
		if (PHYS_collide_tri_seg(obj->vs[obj->fs[i].id[0]].co,
								 obj->vs[obj->fs[i].id[1]].co,
								 obj->vs[obj->fs[i].id[2]].co,
								 pos, oldpos, cp)) {
			vec_cpy(pos, cp);
			return;
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
	static int i = 0;
	if (!i++) {
		//printf("%g %g %g\n",
		//		n[0], n[1], n[2]);
	}
	if (i > 200) i=0;
	float a = PHYS_classify_plane_point(n, p, s1);
	float b = PHYS_classify_plane_point(n, p, s2);
	//if (s1[1]*s2[1] < 0)
	//	printf("%g %g %g      %g %g %g      %g %g\n",
	//			s1[0], s1[1], s1[2], s2[0], s2[1], s2[2], a, b);

	if ((a>0 && b>0) || (a<0 && b<0))
		return 0;
	printf("1\n");

	float d[3];
	vec_sub(d, s2, s1);
	vec_normv(d);
	vec_mulv(d, fabs(vec_dot(n, s1)-vec_dot(n, p)));
	vec_add(cp, s1, d);
	
	return 1;
}

int  PHYS_classify_plane_point(
	float n[3], float p[3],					// plane (a normal & a point)
	float tp[3])							// the point
{
	return vec_dot(n, tp) - vec_dot(n, p);
}

