
#ifndef __MAN_RES_H__
#define __MAN_RES_H__

#include "VG_fvz.h"
#include "SND_ogg.h"
#include "OBJ_fo.h"
#include "TEX.h"
#include <GL/gl.h>

// MANager of RESources

VG_Graph   * MAN_res_loadvg (const char * name);
SND_Music  * MAN_res_loadsnd(const char * name);
OBJ_Object * MAN_res_loadobj(const char * name);
GLuint       MAN_res_loadtex(const char * name);

#endif

