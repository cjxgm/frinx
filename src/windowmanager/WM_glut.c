
#include "WM_manager.h"
#include <GL/glut.h>

int WM_create(int w, int h, const char * title)
{
	int argc = 0;
	glutInit(&argc, NULL);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(w, h);
	glutCreateWindow(title);
	glutTimerFunc(30, (void *)&KE_init, 0);
	glutIdleFunc((void *)&KE_idle);
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
	
	glClearColor(COLOR_MAIN_BG, 1.0f);

	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	*/
	return 0;
}

void WM_mainloop()
{
	glutMainLoop();
}


