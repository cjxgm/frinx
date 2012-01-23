
#ifndef __FX_SPARTI_H__
#define __FX_SPARTI_H__

// Simple PARTIcle system

#include "KE_math.h"

typedef struct SPartiInfo
{
	long  life;
	long  lifefull;
	float v[3];
	float a[3];
	float pos[3];
}
SPartiInfo;

typedef struct FX_SParti
{
	int active;	// active particles' amount
	int amount;
	SPartiInfo * ps;		// particles
}
FX_SParti;

FX_SParti * FX_sparti_new(int amount);
// initial acceleration, velocity, position, the particle life,
// and the randomness for a0, v0, pos0 and life.
void FX_sparti_init(FX_SParti * sp,
					float a0[3], float v0[3], float pos0[3],
					float life,  float arand, float vrand,
					float prand, float lrand);
void FX_sparti_calc(FX_SParti * sp);
void FX_sparti_draw(FX_SParti * sp, float color[3]);

#endif

