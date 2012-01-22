
#ifndef __VG_H__
#define __VG_H__

// Bezier line drawing functionalities.
// Math part is in <kernel>.

#include "KE_link.h"
#include <GL/gl.h>

typedef struct VecGraph
{
	Link eqts;		// bezier equations
}
VecGraph;

// bezier curves are stored as parameter functions, whose parameter is "t".
// tbegin,tend <- [0, 1];	tprec <- (0, 1)
// the curve is more curvy when tprec is rather small (but still larger
// than zero!)

// example: VG_draw(vg, 0.2f, 0.5f, 1e-3f, GL_LINE_STRIP);
void VG_draw(VecGraph * vg, float tbegin, float tend, float tprec,
													GLenum primitive);

#endif

