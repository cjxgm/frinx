
#ifndef __OBJ_H__
#define __OBJ_H__


typedef struct OBJ_Coord
{
	float co[3];
}
OBJ_Coord;

typedef struct OBJ_Face
{
	unsigned short id[3];
	float		   uv[3][2];
}
OBJ_Face;

typedef struct OBJ_Frame
{
	OBJ_Coord * vs;			// vertices
}
OBJ_Frame;

typedef struct OBJ_Action
{
	char * name;
	unsigned char frame_cnt;
	OBJ_Frame * frames;
}
OBJ_Action;

typedef struct OBJ_Object
{
	OBJ_Face   * fs;
	OBJ_Action * as;
	unsigned short fs_cnt;	// faces count
	unsigned short vs_cnt;	// vertices count
	unsigned char  as_cnt;	// actions count
	//			   ns_cnt = fs_cnt, one normal per face
	unsigned short tpf;		// time per frame


	////// only exist in memory
	float pos[3], rot[3];	// position and rotation
	unsigned int   tex;		// texture
	// animation data
	long time_begin;		// when did the animation began?
	int  anim_playing;		// current playing animation
}
OBJ_Object;




void OBJ_free(OBJ_Object * obj);
void OBJ_draw(OBJ_Object * obj);

void OBJ_playanim(OBJ_Object * obj, const char * name);
void OBJ_stopanim(OBJ_Object * obj);

// determine if a given animation is now playing
int  OBJ_isanim(OBJ_Object * obj, const char * name);

#endif

