
#include "WM.h"
#include "SND.h"
#include "FON.h"

int main()
{
	SND_init();
	FON_init(24);
	WM_create(640, 480, "FrinX Game Engine");
	WM_mainloop();

	SND_destroy();
	return 0;
}

