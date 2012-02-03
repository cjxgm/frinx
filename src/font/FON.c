
#include "FON.h"
#include "WM.h"
#include "KE_util.h"
#include <GL/gl.h>
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

	// upside-down reverse
	unsigned char * px = malloc(text->w * text->h * clr_cnt);
	int ix, iy, i;
	for (iy=0; iy<text->h; iy++)
		for (ix=0; ix<text->w; ix++)
			for (i=0; i<clr_cnt; i++)
				px[(iy*text->w+ix)*clr_cnt+i] = ((unsigned char *)
					text->pixels)[((text->h-iy-1)*text->w+ix)*clr_cnt+i];

	CREATE(FON_Text, txt);
	txt->px = px;
	txt->w = text->w;
	txt->h = text->h;
	txt->fmt = tex_fmt;

	SDL_FreeSurface(text);
	return txt;
}

void FON_drawtext(int x, int y, FON_Text * txt)
{
	void glWindowPos2i(int, int);	// I don't know why must I define this.
	glWindowPos2i(x, WM_winh-y-txt->h);
	glDrawPixels(txt->w, txt->h, txt->fmt, GL_UNSIGNED_BYTE, txt->px);
}

void FON_freetext(FON_Text * txt)
{
	free(txt->px);
	free(txt);
}

