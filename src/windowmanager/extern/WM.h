
#ifndef __WM_H__
#define __WM_H__

extern void KE_init();
extern void KE_idle();
int WM_create(int w, int h, const char * title);
void WM_mainloop();

#endif

