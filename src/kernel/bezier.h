
#ifndef ___KE_BEZIER_H___
#define ___KE_BEZIER_H___

#include "KE_link.h"

typedef struct BezEqt3
{
	LINKABLE(struct BezEqt3);
	float eqts[3][4];		// 3 equations for 3 axis
}
BezEqt3;

void bez_eqt_get(float eqt[4], float vals[4]);
float bez_eqt_eval(float eqt[4], float t);

BezEqt3 * bez_eqt3_get(float points[4][3]);
void bez_eqt3_eval(BezEqt3 * eqt3, float t, float result[3]);

#endif

