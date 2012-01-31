
#include "MAN_res.h"
#include <stdio.h>
#include <assert.h>

static char filename[256];

VG_Graph * MAN_res_loadvg(const char * name)
{
	sprintf(filename, "res/vecgraph/%s", name);
	VG_Graph * res = VG_fvz_load(filename);
	assert(res);
	return res;
}

SND_Music * MAN_res_loadsnd(const char * name)
{
	sprintf(filename, "res/sound/%s", name);
	SND_Music * res = SND_ogg_load(filename);
	assert(res);
	return res;
}

OBJ_Object * MAN_res_loadobj(const char * name)
{
	sprintf(filename, "res/object/%s", name);
	OBJ_Object * res = OBJ_fo_load(filename);
	assert(res);
	res->tex = MAN_res_loadtex(name);
	return res;
}

GLuint MAN_res_loadtex(const char * name)
{
	sprintf(filename, "res/texture/%s", name);
	int res = TEX_load(filename);
	assert(res != -1);
	return res;
}

