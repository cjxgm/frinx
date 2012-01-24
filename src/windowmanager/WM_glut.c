
#include "WM.h"
#include "KE.h"
#include <GL/glut.h>
#include <stdlib.h>

static void init_func()
{
	KE_init();
	glutIdleFunc((void *)&KE_idle);
}

static void keybd(unsigned char k, int x, int y)
{
	switch (k) {
		case '\e': exit(0);
	}
}

int WM_create(int w, int h, const char * title)
{
	int argc = 0;
	glutInit(&argc, NULL);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(w, h);
	glutCreateWindow(title);
	glutTimerFunc(30, (void *)&init_func, 0);
	glutKeyboardFunc(&keybd);
	glutFullScreen();
/*
	glutMouseFunc(&click);
	glutMotionFunc(&drag);
	glutPassiveMotionFunc(&hover);


	glutReshapeFunc(&resize);
	glutDisplayFunc(&display);
#ifdef FULLSCREEN
#endif
	*/
	
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
	glutMainLoop();
}


