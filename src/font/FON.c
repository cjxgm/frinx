
#include "FON.h"
#include "WM.h"
#include "KE_util.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL_ttf.h>
#include <assert.h>
#include <stdlib.h>

static TTF_Font * font;

void FON_init(int size)
{
	TTF_Init();
	font = TTF_OpenFont("res/font", size);
	assert(font);
}

void FON_render(int x, int y, const char * str, int r, int g, int b)
{
	FON_Text * txt = FON_gettext(str, r, g, b);
	FON_drawtext(x, y, txt);
	FON_freetext(txt);
}

FON_Text * FON_gettext(const char * str, int r, int g, int b)
{
	SDL_Color color = {.r = r, .g = g, .b = b, .unused = 255};
	SDL_Surface * text = TTF_RenderUTF8_Blended(font, str, color);
	assert(text);

	int clr_cnt = text->format->BytesPerPixel;
	int tex_fmt;
	if (clr_cnt == 4) {
		if (text->format->Rmask == 0x000000FF)
			 tex_fmt = GL_RGBA;
		else tex_fmt = GL_BGRA;
	}
	else if (clr_cnt == 3) {
		if (text->format->Rmask == 0x000000FF)
			 tex_fmt = GL_RGB;
		else tex_fmt = GL_BGR;
	}
	else assert(!"Unknown surface format.");

	CREATE(FON_Text, txt);
	txt->realw = text->w;
	txt->realh = text->h;
	for (txt->w=1; txt->w < text->w; txt->w<<=1);
	for (txt->h=1; txt->h < text->h; txt->h<<=1);
	unsigned char * px = calloc(clr_cnt, txt->w * txt->h);

	int x, y, i;
	for (y=0; y<text->h; y++)
		for (x=0; x<text->w; x++)
			for (i=0; i<clr_cnt; i++)
				px[(y*txt->w + x)*clr_cnt + i] =
			((unsigned char *)text->pixels)[(y*text->w + x)*clr_cnt + i];

	glGenTextures(1, &txt->tex);
	glBindTexture(GL_TEXTURE_2D, txt->tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  
	glTexImage2D(GL_TEXTURE_2D, 0, clr_cnt, txt->w, txt->h,
			0, tex_fmt, GL_UNSIGNED_BYTE, px);

	int err = glGetError();
	if (err != GL_NO_ERROR) {
		printf("OpenGL Error: %s\n", gluErrorString(err));
		assert(err == GL_NO_ERROR);
	}
	SDL_FreeSurface(text);
	return txt;
}

void FON_drawtext(int x, int y, FON_Text * txt)
{
	y = WM_winh - y - txt->h;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, txt->tex);
	glBegin(GL_QUADS); {
		glTexCoord2f(0, 1);
		glVertex2f(x, y);
		glTexCoord2f(1, 1);
		glVertex2f(x+txt->w, y);
		glTexCoord2f(1, 0);
		glVertex2f(x+txt->w, y+txt->h);
		glTexCoord2f(0, 0);
		glVertex2f(x, y+txt->h);
	} glEnd();
	glDisable(GL_TEXTURE_2D);
}

void FON_freetext(FON_Text * txt)
{
	glDeleteTextures(1, &txt->tex);
	free(txt);
}

