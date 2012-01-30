
#ifndef __OBJ_H__
#define __OBJ_H__


typedef struct OBJ_Vertex
{
	float co[3];
}
OBJ_Vertex;

typedef struct OBJ_Face
{
	unsigned short id[3];
}
OBJ_Face;

typedef struct OBJ_Object
{
	OBJ_Vertex * vs;
	OBJ_Face   * fs;
	unsigned short vs_cnt;
	unsigned short fs_cnt;
}
OBJ_Object;

void OBJ_draw(OBJ_Object * obj);
void OBJ_free(OBJ_Object * obj);

#endif

