
#include "WM.h"
#include "SND.h"
#include "FON.h"

int main()
{
	SND_init();
	FON_init(20);
	WM_create(760, 480, "FrinX Game Engine");
	WM_mainloop();

	SND_destroy();
	return 0;
}

