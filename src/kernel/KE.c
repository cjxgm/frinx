
#include "KE.h"
#include "KE_time.h"
#include "REN_logo.h"
#include "WM.h"
#include <GL/gl.h>

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
	long time_begin = KE_time_get();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	((void (*)())renderer)();
	WM_swap();

	long time_end = KE_time_get();
	KE_mspf = time_end - time_begin;
	KE_spf  = KE_mspf / 1000.0f;
	printf("\r%ld ms per frame = %.3f fps          ", KE_mspf, 1000.0f / KE_mspf);
	fflush(stdout);
}

void KE_set_renderer(void * _renderer)
{
	renderer = _renderer;
}

static void no_renderer()
{
}

