
#ifndef __WM_H__
#define __WM_H__

#include "../WM_sdl.h"

extern int WM_winw;
extern int WM_winh;
extern const char * WM_wintitle;

extern unsigned char WM_key[384];
extern unsigned char WM_keydown;
extern unsigned short WM_kmod;

int WM_create(int w, int h, const char * title);
void WM_mainloop();
void WM_swap();

#endif

