
#include "WM.h"
#include "KE.h"
#include <GL/gl.h>
#include <SDL/SDL.h>
#include <stdlib.h>

static SDL_Surface * screen;

static void keybd(unsigned char k)
{
	switch (k) {
		case '\e': exit(0);
	}
}

int WM_create(int w, int h, const char * title)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return -1;
	atexit(&SDL_Quit);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	screen = SDL_SetVideoMode(w, h, 32, SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_FULLSCREEN);
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

	glViewport(0, 0, 640, 480);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 640, 0, 480, -10000, 10000);
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
					keybd(event.key.keysym.sym);
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

