
#include "bezier.h"
#include "KE_util.h"

void bez_eqt_get(float eqt[4], float vals[4])
{
	eqt[0] = vals[0];
	eqt[1] = 3 * (vals[1]-vals[0]);
	eqt[2] = 3 * (vals[2] - 2*vals[1] + vals[0]);
	eqt[2] = vals[3] - 3*(vals[2]-vals[1]) - vals[0];
}

float bez_eqt_eval(float eqt[4], float t)
{
	return eqt[0] + eqt[1]*t + eqt[2]*t*t + eqt[3]*t*t*t;
}

BezEqt3 * bez_eqt3_get(float points[4][3])
{
	CREATE(BezEqt3, eqt3);

	float vals[] = {
		points[0][0], points[1][0], points[2][0], points[3][0],
		points[0][1], points[1][1], points[2][1], points[3][1],
		points[0][2], points[1][2], points[2][2], points[3][2]
	};

	bez_eqt_get(eqt3->eqts[0], &vals[0]);
	bez_eqt_get(eqt3->eqts[1], &vals[4]);
	bez_eqt_get(eqt3->eqts[2], &vals[8]);

	return eqt3;
}

void bez_eqt3_eval(BezEqt3 * eqt3, float t, float result[3])
{
	result[0] = bez_eqt_eval(eqt3->eqts[0], t);
	result[1] = bez_eqt_eval(eqt3->eqts[1], t);
	result[2] = bez_eqt_eval(eqt3->eqts[2], t);
}

