
#include "WM.h"
#include "KE.h"
#include <GL/gl.h>
#include <SDL/SDL.h>

static SDL_Surface * screen;
int WM_winw = 320;
int WM_winh = 240;
const char * WM_wintitle = "FrinX Game Engine";
unsigned char WM_key[384] = {0};
unsigned char WM_keydown = 0;
unsigned short WM_kmod = WM_KMOD_NONE;

int WM_create(int w, int h, const char * title)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return -1;
	atexit(&SDL_Quit);

	WM_winw = w;
	WM_winh = h;
	WM_wintitle = title;

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	screen = SDL_SetVideoMode(w, h, 32, SDL_OPENGL | SDL_GL_DOUBLEBUFFER
				/* | SDL_FULLSCREEN */ );
	SDL_WM_SetCaption(title, NULL);
	SDL_ShowCursor(SDL_DISABLE);

	/*glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(w, h);
	glutCreateWindow(title);
	glutTimerFunc(30, (void *)&init_func, 0);
	glutKeyboardFunc(&keybd);
	glutFullScreen();
	*/
/*
	glutMouseFunc(&click);
	glutMotionFunc(&drag);
	glutPassiveMotionFunc(&hover);


	glutReshapeFunc(&resize);
	glutDisplayFunc(&display);
#ifdef FULLSCREEN
#endif
	*/

	KE_init();
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -10000, 10000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	return 0;
}

void WM_mainloop()
{
	// glutMainLoop();
	int cont = 1;
    SDL_Event event;

	while (cont) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					cont = 0;
					break;
				case SDL_KEYDOWN:
					WM_key[event.key.keysym.sym] = 1;
					WM_kmod = SDL_GetModState();
					WM_keydown = 1;
					break;
				case SDL_KEYUP:
					WM_key[event.key.keysym.sym] = 0;
					WM_kmod = SDL_GetModState();
					WM_keydown = 0;
					break;
			}
		}
		KE_idle();
	}

	SDL_Quit();
}

void WM_swap()
{
	SDL_GL_SwapBuffers();
}

