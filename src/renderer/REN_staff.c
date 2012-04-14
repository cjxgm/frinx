
#include "REN_staff.h"
#include "KE_time.h"
#include "KE_math.h"
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
	{"FrinX Development Team", NULL, 1700},
	{"Engine", NULL, 2000},
	{"Chief Programmer", "eXerigumo Clanjor(哆啦比猫/兰威举)", 3300},
	{"Designing Leader", "eXerigumo Clanjor(哆啦比猫/兰威举)", 3300},
	{"Artworks", NULL, 3700},
	{"Logo Design", "Sun Kowul", 3300},
	{"Logo Design", "Remind", 3300},
	{"CG", "eXerigumo Clanjor(哆啦比猫/兰威举)", 3300},
	{"Relative Services", NULL, 3700},
	{"Web Design", "eXerigumo Clanjor(哆啦比猫/兰威举)", 2000},
	{"Web Coding", "eXerigumo Clanjor(哆啦比猫/兰威举)", 2000},
	{"Present", "Clanjor Productions", 2000},
	{"Supports", NULL, 3700},
	{"Special Thanks to", "Masta Zheng(郑志明) as our actor", 3300},
	{"Special Thanks to", "ArchLinux", 2000},
	{"Special Thanks to", "Blender", 2000},
	{"Special Thanks to", "Vim", 2000},
	{"Special Thanks to", "SConstruct", 2000},
	{"Special Thanks to", "OpenGL", 2000},
	{"Special Thanks to", "SDL, SDL_mixer, SDL_image, SDL_ttf", 2000},
	{"Special Thanks to", "FreeType", 2000},
	{"Special Thanks to", "Ogg Vorbis", 2000},
#ifdef _WIN32
	{"Special Thanks to", "Dev-C++, MinGW", 2000},
#endif
	{"Special Thanks to", "MilkyTracker", 2000},
	{"Special Thanks to", "Inkscape", 2000},
	{"Special Thanks to", "GIMP", 2000},
	{"Special Thanks to", "zlib", 2000},
	{"Special Thanks to", "gcc", 2000},
	{"Special Thanks to", "python", 2000},
	{"Special Thanks to", "git and github.com", 2000},
	{"Special Thanks to", "modules.pl", 2000},
	{"Special Thanks to", "dot.tk", 2000},
	{"Copyrights", NULL, 2000},
	{"Source Code License", "GNU General Public Licence version 2", 3300},
	{"Artwork License", "Creative Commons Attribution CC-BY-SA 3.0", 3300},
	{"Copyright", "(C) Wolf King Studio, 2012.", 3300},
	{"Copyright", "(C) Clanjor Productions, 2010-2012.", 3300},
#ifdef _WIN32
	{"Window$ Sucks", "It's really difficult to port this to Window$...", 5300},
#endif
	{"FrinX Game Engine", NULL, 0},
};

static int sid = 0;		// current staff id
static long te = 0;		// time ellapsed


void REN_staff_init()
{
	music = MAN_res_loadsnd("staff");

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WM_winw/(WM_naked3d+1), 0, WM_winh, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	int i;
	for (i=0; i<LEN(staff); i++) {
		staff[i].text[0] = FON_gettext(staff[i].item, 255, 255*0.8, 0);
		if (staff[i].str)
			staff[i].text[1] = FON_gettext(staff[i].str , 0, 255*0.8, 255);
		else staff[i].text[1] = NULL;
	}

	SND_playmusic(music);
}

static void draw(int isright)
{
	if (te + staff[sid].time < KE_time_get())
		if (sid < LEN(staff)-1) {
			te += staff[sid].time;
			sid++;
		}

	glPushMatrix();

	float offset = (WM_naked3d ? 1-2*isright : 0);
	float offset_title = 0;
	float offset_item  = 0;

	int rt = KE_time_get() - te;	// relative time
	if (rt < 500) {
		glColor4f(1, 1, 1, lirp(rt, 0, 500, 0, 1));
		glRotatef(lirp(rt, 0, 500, 60, 0), 0, 0, 1);
		glScalef(lirp(rt, 0, 500, 10, 1), lirp(rt, 0, 500, 0, 1), 1);
	}
	else if (sid != LEN(staff)-1 && (rt -= staff[sid].time) > -500) {
		glColor4f(1, 1, 1, lirp(rt, -500, 0, 1, 0));
		glRotatef(lirp(rt, -500, 0, 0, 60), 0, 0, 1);
		glScalef(lirp(rt, -500, 0, 1, 0), lirp(rt, -500, 0, 1, 0), 1);
	}
	else {
		glColor4f(1, 1, 1, 1);
		offset_title = offset * lirp(rt, -staff[sid].time+500, -500, 10, 1);
		offset_item  = offset * lirp(rt, -staff[sid].time+500, -500, 2, 15);
	}


	if (staff[sid].text[1]) {
		FON_drawtext((WM_winw/(WM_naked3d+1) - staff[sid].text[0]->realw)/2
						+ offset_title,
					 WM_winh/2 - 15,
					 staff[sid].text[0]);
		FON_drawtext((WM_winw/(WM_naked3d+1) - staff[sid].text[1]->realw)/2
						+ offset_item,
					 WM_winh/2 + 15,
					 staff[sid].text[1]);
	}
	else
		FON_drawtext((WM_winw/(WM_naked3d+1) - staff[sid].text[0]->realw)/2
						+ offset_title,
					 (WM_winh - staff[sid].text[0]->realh)/2,
					 staff[sid].text[0]);

	glPopMatrix();
}


void REN_staff()
{
	// when playing began, reset time;
	// when it ended, exit
	static int play_began = 0;
	if (SND_is_playing()) {
		if (!play_began) {
			play_began = 1;

			glDisable(GL_LIGHTING);	// this must be here, not in init!

			KE_time_reset();
		}
	}
	else if (play_began)
		exit(0);
	else return;

	if (WM_keydown)
		exit(0);

	if (WM_naked3d) {
		glViewport(0, 0, WM_winw/2, WM_winh);
		draw(0);
		glViewport(WM_winw/2, 0, WM_winw/2, WM_winh);
		draw(1);
	}
	else draw(0);
}

