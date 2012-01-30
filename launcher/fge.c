
#include "WM.h"
#include "SND.h"
#include "SND_ogg.h"

int main()
{
	SND_init();
	WM_create(640, 480, "FrinX Game Engine");
	WM_mainloop();

	SND_destroy();
	return 0;
}

