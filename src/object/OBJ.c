
#include "OBJ.h"
#include "KE_time.h"
#include "KE_math.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <GL/gl.h>

#include <stdio.h>	// debug use

void OBJ_free(OBJ_Object * obj)
{
	/*FIXME: 
	free(obj->vs);
	free(obj->fs);
	free(obj->ns);
	free(obj);
	*/
}

void OBJ_draw(OBJ_Object * obj)
{
	if (obj->anim_playing == -1)
		OBJ_playanim(obj, "static");

	OBJ_Action * act = &obj->as[obj->anim_playing];

	int t = KE_time_get() - obj->time_begin;
	t %= obj->tpf * act->frame_cnt;
	int frame1 = t / obj->tpf;
	int frame2 = (frame1 + 1) % act->frame_cnt;
	float foffset = (float)(t - frame1 * obj->tpf) / (float)obj->tpf;

	float normal[3], co[3][3];

	glBindTexture(GL_TEXTURE_2D, obj->tex);
	glBegin(GL_TRIANGLES);
	int i;
	for (i=0; i<obj->fs_cnt; i++) {
		// calculate animation
		vec_lirp(co[0], foffset,
				act->frames[frame1].vs[obj->fs[i].id[0]].co,
				act->frames[frame2].vs[obj->fs[i].id[0]].co);
		vec_lirp(co[1], foffset,
				act->frames[frame1].vs[obj->fs[i].id[1]].co,
				act->frames[frame2].vs[obj->fs[i].id[1]].co);
		vec_lirp(co[2], foffset,
				act->frames[frame1].vs[obj->fs[i].id[2]].co,
				act->frames[frame2].vs[obj->fs[i].id[2]].co);
		vec_unit_normal_3p(normal, co[0], co[1], co[2]);

		
		// draw
		glNormal3fv(normal);

		glTexCoord2fv(obj->fs[i].uv[0]);
		glVertex3fv(co[0]);

		glTexCoord2fv(obj->fs[i].uv[1]);
		glVertex3fv(co[1]);

		glTexCoord2fv(obj->fs[i].uv[2]);
		glVertex3fv(co[2]);
	}
	glEnd();
}

void OBJ_playanim(OBJ_Object * obj, const char * name)
{
	int i;
	for (i=0; i<obj->as_cnt; i++)
		if (strcmp(name, obj->as[i].name) == 0)
			break;
	assert(i != obj->as_cnt || "Action not found.");

	obj->anim_playing = i;
	obj->time_begin = KE_time_get();
}

void OBJ_stopanim(OBJ_Object * obj)
{
	OBJ_playanim(obj, "static");
}

