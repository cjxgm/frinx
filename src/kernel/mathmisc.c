
#include "mathmisc.h"

// Linear InteRPolation
float lirp(float v, float vf, float vt, float df, float dt)
{
	return (v-vf) / (vt-vf) * (dt-df) + df;
}

// Amazing Fast SQuare RooT
// I grabbed this code from wikipedia.
// It comes from Quake III engine.
float afsqrt(float x)
{
	union {
		float x;
		int i;
	} u;

	u.x = x;
	u.i = 0x5f3759df - (u.i >> 1);
	x = u.x * (1.5f - 0.5f * x * u.x * u.x);

	return 1.0f / x;
}

