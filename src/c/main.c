#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include "renderer.h"


void renderScene() {
	clearDisplay();
	
	swapBuffers();
}
int main() {
	initDisplay(500, 500, "OpenFTL");
	
	setRenderFunction(renderScene);

	startMainLoop();
	return 0;
}
