
#include "OBJ_fo.h"
#include "KE_util.h"
#include "KE_math.h"
#include <assert.h>

OBJ_Object * OBJ_fo_load(const char * file)
{
	FILE * fp = fopen(file, "r");
	if (!fp) return NULL;

	CREATE(OBJ_Object, obj);
	int i;

	unsigned char mesh_cnt;
	READ(mesh_cnt, fp);
	assert(mesh_cnt == 1 && "Only supports ONE mesh in one object now.");

	// read vertices
	READ(obj->vs_cnt, fp);
	obj->vs = malloc(sizeof(OBJ_Vertex) * obj->vs_cnt);
	READ_ARRAY(obj->vs, obj->vs_cnt, fp);
	// flip uv coord
	for (i=0; i<obj->vs_cnt; i++)
		obj->vs[i].uv[1] = 1.0f - obj->vs[i].uv[1];

	// read faces
	READ(obj->fs_cnt, fp);
	obj->fs = malloc(sizeof(OBJ_Face) * obj->fs_cnt);
	READ_ARRAY(obj->fs, obj->fs_cnt, fp);
	// calculate normals
	obj->ns = malloc(sizeof(OBJ_Coord) * obj->fs_cnt);
	for (i=0; i<obj->fs_cnt; i++) {
		float v[2][3];
		vec_sub(v[0], obj->vs[obj->fs[i].id[1]].co,
					  obj->vs[obj->fs[i].id[0]].co);
		vec_sub(v[1], obj->vs[obj->fs[i].id[2]].co,
					  obj->vs[obj->fs[i].id[0]].co);
		vec_unit_normal(obj->ns[i].co, v[0], v[1]);
	}

	fclose(fp);
	return obj;
}

