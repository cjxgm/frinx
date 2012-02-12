
#include "REN_staff.h"
#include "KE_time.h"
#include "KE_util.h"
#include "KE.h"
#include "WM.h"
#include "FON.h"
#include "MAN_res.h"
#include <stdlib.h>
#include <SDL/SDL.h>
#include <GL/gl.h>

static SND_Music * music;

typedef struct Staff
{
	const char * item;
	const char * str;
	long         time;
	FON_Text   * text[2];
}
Staff;

static Staff staff[] = {
	// There cannot be any EMPTY STRING!
	{"FrinX Development Team", " ", 3000},
	{"Chief Programmer", "eXerigumo Clanjor(哆啦比猫/兰威举)", 3000},
	{"Design", "eXerigumo Clanjor(哆啦比猫/兰威举)", 3000},
	{"FrinX Game Engine", " ", 0},
};

static int sid = 0;		// current staff id
static long te = 0;		// time ellapsed


void REN_staff_init()
{
	music = MAN_res_loadsnd("staff");

	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	glViewport(0, 0, WM_winw, WM_winh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WM_winw, 0, WM_winh, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	int i;
	for (i=0; i<LEN(staff); i++) {
		staff[i].text[0] = FON_gettext(staff[i].item, 255, 255, 128);
		staff[i].text[1] = FON_gettext(staff[i].str , 255, 255, 255);
	}

	SND_playmusic(music);
}

void REN_staff()
{
	// when playing began, reset time;
	// when it ended, exit
	static int play_began = 0;
	if (SND_is_playing()) {
		if (!play_began) {
			play_began = 1;
			KE_time_reset();
		}
	}
	else if (play_began)
		exit(0);
	else return;

	if (WM_keydown)
		exit(0);

	if (te + staff[sid].time >= KE_time_get())
		if (sid+1 < LEN(staff))
			sid++;
	
	FON_drawtext(10, WM_winh/4   , staff[sid].text[0]);
	FON_drawtext(50, WM_winh/4+30, staff[sid].text[1]);
}


