
#ifndef __WM_H__
#define __WM_H__

extern int WM_winw;
extern int WM_winh;
extern const char * WM_wintitle;

int WM_create(int w, int h, const char * title);
void WM_mainloop();
void WM_swap();

#endif

