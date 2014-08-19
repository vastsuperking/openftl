#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>

void initDisplay(int width, int height, char *name) {
	int argc = 1;
	char *myargv[1];

	myargv[0] = name;
	glutInit(&argc, myargv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow(name);
}
void setRenderFunction(void (*func)(void)) {
	glutDisplayFunc(func);
}

void startMainLoop() {
	glutMainLoop();
}

void clearDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void swapBuffers() {
	glutSwapBuffers();
}


void renderQuad() {
	
}
