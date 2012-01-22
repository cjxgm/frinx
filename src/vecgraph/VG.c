
#include "VG.h"
#include "KE_link.h"
#include "KE_math.h"
#include <assert.h>

void VG_plot(VecGraph * vg, float tbegin, float tend, float tprec)
{
	assert(vg);
	assert(tprec >= 0.0f && tprec < 1.0f);
	assert(tbegin < tend - tprec);

	{ TRAVERSE(&vg->eqts, BezEqt3, eqt3) {
		float t;
		for (t=tbegin; t<=tend; t+=tprec) {
			float result[3];
			bez_eqt3_eval(eqt3, t, result);
			glVertex3fv(result);
		}
	}}
}

void VG_draw(VecGraph * vg, float tbegin, float tend, float tprec,
													GLenum primitive)
{
	glBegin(primitive);
	VG_plot(vg, tbegin, tend, tprec);
	glEnd();
}

