
#ifndef __WM_H__
#define __WM_H__

#include "../WM_sdl.h"

extern int WM_winw;
extern int WM_winh;
extern const char * WM_wintitle;

extern unsigned char WM_key[384];
extern unsigned char WM_keydown;
extern unsigned short WM_kmod;

extern int WM_naked3d;

int WM_create(int w, int h, const char * title);
void WM_mainloop();
void WM_swap();

void WM_get_relative_mouse_pos(int * x, int * y);

#endif

