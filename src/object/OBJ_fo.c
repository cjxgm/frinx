
#include "OBJ_fo.h"
#include "KE_util.h"
#include <assert.h>

OBJ_Object * OBJ_fo_load(const char * file)
{
	FILE * fp = fopen(file, "r");
	assert(fp != NULL);

	CREATE(OBJ_Object, obj);

	unsigned char mesh_cnt;
	READ(mesh_cnt, fp);
	assert(mesh_cnt == 1 && "Only supports ONE mesh in one object now.");

	// read vertices
	READ(obj->vs_cnt, fp);
	obj->vs = malloc(sizeof(OBJ_Vertex) * obj->vs_cnt);
	READ_ARRAY(obj->vs, obj->vs_cnt, fp);

	// read faces
	READ(obj->fs_cnt, fp);
	obj->fs = malloc(sizeof(OBJ_Face) * obj->fs_cnt);
	READ_ARRAY(obj->fs, obj->fs_cnt, fp);

	fclose(fp);
	return obj;
}

