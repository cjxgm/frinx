
// Simple PARTIcle system

#include "FX_sparti.h"
#include "KE.h"
#include "KE_util.h"
#include <GL/gl.h>

FX_SParti * FX_sparti_new(int amount)
{
	CREATE(FX_SParti, sp);
	sp->amount = amount;
	sp->active = 0;
	sp->elapse = 0;
	sp->time   = 0;
	sp->ps = malloc(sizeof(SPartiInfo)*amount);
	return sp;
}

void FX_sparti_init(FX_SParti * sp,
					float a0[3], float v0[3],   float pos0[3],
					float life,  long emittime, float _arand,
					float _vrand,float _prand,  float _lrand)
{
#define RAND(V)		(((rand()%1001)-500) / 500.0f * (V))
	sp->active = sp->amount;
	sp->time   = emittime;

	int i;
	for (i=0; i<sp->amount; i++) {
		float arand[] = { RAND(_arand), RAND(_arand), RAND(_arand) };
		float vrand[] = { RAND(_vrand), RAND(_vrand), RAND(_vrand) };
		float prand[] = { RAND(_prand), RAND(_prand), RAND(_prand) };
		vec_add(sp->ps[i].a, a0, arand);
		vec_add(sp->ps[i].v, v0, vrand);
		vec_add(sp->ps[i].pos, pos0, prand);
		sp->ps[i].lifefull = life + RAND(_lrand);
		if (sp->ps[i].lifefull > 0)
			sp->ps[i].life = sp->ps[i].lifefull;
		else {
			sp->ps[i].lifefull = 0;
			sp->ps[i].life = 0;
			sp->active--;
		}
	}
#undef RAND
}

void FX_sparti_calc(FX_SParti * sp)
{
	int i;

	int amount = sp->amount;
	if (sp->time)
		amount = (float)sp->elapse / (float)sp->time * sp->amount + 1;
	if (amount > sp->amount) amount = sp->amount;

	sp->elapse += KE_mspf;

	for (i=0; i<amount; i++) {
		if (!sp->ps[i].life) continue;
		sp->ps[i].life -= KE_mspf;
		if (sp->ps[i].life < 0) sp->ps[i].life = 0;

		// pos> += v> * t + 1/2 * a> * t^2
		float vt[3];
		float half_at_sqr[3];
		vec_mul(vt, sp->ps[i].v, KE_spf);
		vec_mul(half_at_sqr, sp->ps[i].a, KE_spf * KE_spf * 0.5f);
		vec_addv(sp->ps[i].pos, vt);
		vec_addv(sp->ps[i].pos, half_at_sqr);

		// v> += a> * t
		vec_mul(vt, sp->ps[i].a, KE_spf);
		vec_addv(sp->ps[i].v, vt);
	}
}

void FX_sparti_draw(FX_SParti * sp, float color[3])
{
	int amount = sp->amount;
	if (sp->time)
		amount = (float)sp->elapse / (float)sp->time * sp->amount + 1;
	if (amount > sp->amount) amount = sp->amount;

	glBegin(GL_POINTS);
	int i;
	for (i=0; i<amount; i++) {
		if (!sp->ps[i].life) continue;
		glColor4f(color[0], color[1], color[2],
					(float)sp->ps[i].life / (float)sp->ps[i].lifefull);
		glVertex3fv(sp->ps[i].pos);
	}
	glEnd();
}

