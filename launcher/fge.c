
#include "WM_manager.h"
#include "SND_manager.h"
#include "SND_ogg.h"

int main()
{
	SND_init();
	WM_create(640, 480, "Frinx Game Engine");
	WM_mainloop();

	SND_destroy();
	return 0;
}

