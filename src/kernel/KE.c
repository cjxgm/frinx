
#include "KE.h"
#include "REN_logo.h"
#include "WM.h"
#include <GL/gl.h>
#include <time.h>

long KE_mspf = 10;
float KE_spf = 0.01f;

static void no_renderer();
static void * renderer = &no_renderer;

void KE_init()
{
	KE_SET_RENDERER(logo);
}

void KE_idle()
{
	long time_begin = clock();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	((void (*)())renderer)();
	WM_swap();

	long time_end = clock();
	KE_mspf = (time_end - time_begin) * 1000 / CLOCKS_PER_SEC;
	KE_spf  = (float)(time_end - time_begin) / CLOCKS_PER_SEC;
}

void KE_set_renderer(void * _renderer)
{
	renderer = _renderer;
}

static void no_renderer()
{
}

