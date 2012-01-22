
#include "VG_fvz.h"
#include "KE_util.h"
#include "KE_math.h"
#include <assert.h>
#include <zlib.h>

VecGraph * VG_fvz_load(const char * file)
{
	gzFile * gf = gzopen(file, "r");
	assert(gf != NULL);

	CREATE(VecGraph, vg);
	link_init(&vg->eqts);

	float points[4][3];
	points[0][2] = points[1][2] = points[2][2] = points[3][2] = 0;

	while (1) {
		if (gzread(gf, &points[0], sizeof(float)*2) == 0)
			break;
		gzread(gf, points[1], sizeof(float)*2);
		gzread(gf, points[2], sizeof(float)*2);
		gzread(gf, points[3], sizeof(float)*2);
		link_addtail(&vg->eqts, bez_eqt3_get(points));
	}

	gzclose(gf);
	return vg;
}

