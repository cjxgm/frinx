
// interpolation
#include "interp.h"

float lirp(float v, float vf, float vt, float df, float dt)
{
	return (v-vf) / (vt-vf) * (dt-df) + df;
}

