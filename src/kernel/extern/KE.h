
#ifndef __KE_H__
#define __KE_H__

#define KE_SET_RENDERER(NAME)	do { \
	REN_ ## NAME ## _init(); \
	KE_set_renderer(&REN_ ## NAME); \
} while (0)


extern long KE_mspf;	// milliseconds per frame
extern float KE_spf;	// seconds per frame

void KE_init();
void KE_idle();
void KE_set_renderer(void * renderer);

#endif

