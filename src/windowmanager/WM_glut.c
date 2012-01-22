
#include "WM.h"
#include <GL/glut.h>

static void init_func()
{
	KE_init();
	glutIdleFunc((void *)&KE_idle);
}

int WM_create(int w, int h, const char * title)
{
	int argc = 0;
	glutInit(&argc, NULL);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(w, h);
	glutCreateWindow(title);
	glutTimerFunc(30, (void *)&init_func, 0);
/*
	glutMouseFunc(&click);
	glutMotionFunc(&drag);
	glutPassiveMotionFunc(&hover);

	glutKeyboardFunc(&key);

	glutReshapeFunc(&resize);
	glutDisplayFunc(&display);
#ifdef FULLSCREEN
	glutFullScreen();
#endif
	*/
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glViewport(0, 0, 640, 480);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 640, 0, 480, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	return 0;
}

void WM_mainloop()
{
	glutMainLoop();
}


