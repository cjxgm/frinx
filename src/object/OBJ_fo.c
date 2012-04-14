
#include "OBJ_fo.h"
#include "KE_util.h"
#include "KE_math.h"
#include <assert.h>

OBJ_Object * OBJ_fo_load(const char * file)
{
	FILE * fp = fopen(file, "rb");
	if (!fp) return NULL;

	CREATE(OBJ_Object, obj);
	int i, j;

	// read faces
	READ(obj->fs_cnt, fp);
	obj->fs = malloc(sizeof(OBJ_Face) * obj->fs_cnt);
	for (i=0; i<obj->fs_cnt; i++) {
		READ(obj->fs[i].id, fp);
		READ(obj->fs[i].uv, fp);
		// flip y-axis of uv
		obj->fs[i].uv[0][1] = 1.0f - obj->fs[i].uv[0][1];
		obj->fs[i].uv[1][1] = 1.0f - obj->fs[i].uv[1][1];
		obj->fs[i].uv[2][1] = 1.0f - obj->fs[i].uv[2][1];
	}

	// read actions
	READ(obj->vs_cnt, fp);
	READ(obj->tpf, fp);
	READ(obj->as_cnt, fp);
	obj->as = malloc(sizeof(OBJ_Action) * obj->as_cnt);
	for (i=0; i<obj->as_cnt; i++) {
		OBJ_Action * act = &obj->as[i];
		// read name
		unsigned char namelen;
		READ(namelen, fp);
		act->name = malloc(namelen + 1);
		READ_ARRAY(act->name, namelen, fp);
		act->name[namelen] = 0;

		// read frames
		READ(act->frame_cnt, fp);
		act->frames = malloc(sizeof(OBJ_Frame) * act->frame_cnt);
		for (j=0; j<act->frame_cnt; j++) {
			// read vertices
			act->frames[j].vs = malloc(sizeof(OBJ_Coord) * obj->vs_cnt);
			READ_ARRAY(act->frames[j].vs, obj->vs_cnt, fp);
		}
	}


	fclose(fp);

	obj->pos[0] = obj->pos[1] = obj->pos[2] = 0;
	obj->rot[0] = obj->rot[1] = obj->rot[2] = 0;

	OBJ_stopanim(obj);
	return obj;
}

