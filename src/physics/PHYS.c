
#include "PHYS.h"
#include "KE_math.h"
#include "KE.h"

void PHYS_verlet_apply(float pos[3], float oldpos[3], float force[3])
{
	float t[3];
	float fs[3];
	float fr[3];

	vec_cpy(t, pos);
	vec_mul(fs, force, KE_spf*KE_spf);
	vec_sub(fr, pos, oldpos);
	vec_mulv(fr, -0.1);
	vec_addv(fs, fr);

	vec_addv(pos, pos);
	vec_subv(pos, oldpos);
	vec_addv(pos, fs);
	vec_cpy(oldpos, t);
}

void PHYS_con_stick_apply(PHYS_ConStick * con)
{
	float delta[3];
	vec_sub(delta, con->node[1], con->node[0]);
	float dsqr = vec_sqr(delta);
	float lsqr = con->len * con->len;
	float diff = lsqr / (dsqr+lsqr) - 0.5;
	vec_mulv(delta, diff);
	vec_subv(con->node[0], delta);
	vec_addv(con->node[1], delta);
}

