
#include "VG.h"
#include "KE_link.h"
#include "KE_math.h"
#include <assert.h>

void VG_draw(VG_Graph * vg, float tbegin, float tend, float tprec,
													GLenum primitive)
{
	assert(vg);
	assert(tprec >= 0.0f && tprec < 1.0f);

	{ TRAVERSE(&vg->eqts, BezEqt3, eqt3) {
		float t;

		glBegin(primitive);
		for (t=tbegin; t<=tend; t+=tprec) {
			float result[3];
			bez_eqt3_eval(eqt3, t, result);
			glVertex3fv(result);
		}
		glEnd();
	}}
}

