
#ifndef __VG_FVZ_H__
#define __VG_FVZ_H__

#include "VG.h"

// fvz, Frinx Vector gZipped file format:
//		It's rather simple, just groups of four 2d vectors which constructs
//		the bezier curve. Oh, one more thing to say: it's gzipped!

VecGraph * VG_fvz_load(const char * file);

#endif

