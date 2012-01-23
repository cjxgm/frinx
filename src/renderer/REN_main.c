
#include "REN_main.h"
#include "FX_sparti.h"
#include "KE_time.h"
#include <GL/gl.h>

static FX_SParti * sp;

void REN_main_init()
{
	sp = FX_sparti_new(1000);
	float v[] = {0, 0, 0};
	float p[] = {320, 240, 0};
	FX_sparti_init(sp, v, v, p, 2000, 100, 100, 0, 1000);

	KE_time_reset();
}

void REN_main()
{
	glPointSize(10);
	float color[] = {1.0, 0.8, 0.0};
	FX_sparti_draw(sp, color);
	FX_sparti_calc(sp);
}

