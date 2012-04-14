
#include "WM.h"
#include "SND.h"
#include "FON.h"
#include <string.h>

int main(int argc, char * argv[])
{
	WM_naked3d = (argc == 2 && !strcmp(argv[1], "--naked3d"));

	SND_init();
	FON_init(20);
	WM_create((WM_naked3d ? 760 : 640), 480, "FrinX Game Engine");
	WM_mainloop();

	SND_destroy();
	return 0;
}

