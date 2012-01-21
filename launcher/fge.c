
#include "WM_manager.h"
#include "SND_manager.h"
#include "SND_ogg.h"

static void debug();

int main()
{
	debug();
	/*
	SND_init();

	WM_create(640, 480, "Frinx Game Engine");
	WM_mainloop();
	*/

	return 0;
}

static void debug()
{
	SND_init();
	SND_ogg_play("res/sound/music.ogg");
	while (SND_is_playing());
	SND_destroy();
}

