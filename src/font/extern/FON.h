
#ifndef __FONT_H__
#define __FONT_H__

typedef struct FON_Text
{
	unsigned int tex;
	int w, h;
}
FON_Text;


void FON_init(int size);
void FON_render(int x, int y, const char * str, int r, int g, int b);
FON_Text * FON_gettext(const char * str, int r, int g, int b);
void FON_drawtext(int x, int y, FON_Text * txt);
void FON_freetext(FON_Text * txt);

#endif

