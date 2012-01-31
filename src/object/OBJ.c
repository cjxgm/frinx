
#include "OBJ.h"
#include <stdlib.h>
#include <GL/gl.h>

void OBJ_draw(OBJ_Object * obj)
{
	glBegin(GL_TRIANGLES);
	int i;
	for (i=0; i<obj->fs_cnt; i++) {
		glNormal3fv(obj->ns[i].co);
		glTexCoord2fv(obj->vs[obj->fs[i].id[0]].uv);
		glVertex3fv(obj->vs[obj->fs[i].id[0]].co);
		glTexCoord2fv(obj->vs[obj->fs[i].id[1]].uv);
		glVertex3fv(obj->vs[obj->fs[i].id[1]].co);
		glTexCoord2fv(obj->vs[obj->fs[i].id[2]].uv);
		glVertex3fv(obj->vs[obj->fs[i].id[2]].co);
	}
	glEnd();
}

void OBJ_free(OBJ_Object * obj)
{
	free(obj->vs);
	free(obj->fs);
	free(obj->ns);
	free(obj);
}

