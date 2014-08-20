#include <glload/gl_2_0.h>
#include <glload/gl_load.h>
#include <GL/freeglut.h>
#include <stdio.h>

#include "shader_struct.h"
#include "shader.h"

#define MAJOR_CONTEXT_VERSION 2
#define MINOR_CONTEXT_VERSION 0

shader_t *fragShader;
shader_t *vertexShader;
program_t *program;

void initDisplay(int width, int height, char *name) {
	int argc = 1;
	int loadTest;
	char *myargv[1];

	myargv[0] = name;
	glutInit(&argc, myargv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitContextVersion(MAJOR_CONTEXT_VERSION, MINOR_CONTEXT_VERSION);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow(name);

	loadTest = ogl_LoadFunctions();
	if (loadTest == ogl_LOAD_FAILED) printf("Loading opengl function pointers failed!");
}
void initOGL() {
	fragShader = createShaderFromFile(GL_FRAGMENT_SHADER, "fragment.frag");
	vertexShader = createShaderFromFile(GL_VERTEX_SHADER, "vertex.vert");
	program= createProgram(fragShader, vertexShader);
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


void renderQuad(float x, float y, int width, int height) {
}
