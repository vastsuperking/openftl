#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include "renderer.h"


void renderScene() {
	clearDisplay();
	
	swapBuffers();
}
int main() {
	printf("Hello world\n");
	initDisplay(500, 500, "Test");
	
	setRenderFunction(renderScene);

	startMainLoop();
	return 0;
}
