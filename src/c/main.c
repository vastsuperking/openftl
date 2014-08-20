#include <stdio.h>
#include <glload/gl_2_0.h>
#include "renderer.h"
#include "shader_struct.h"
#include "shader.h"



void renderScene() {
	clearDisplay();
	swapBuffers();
}
int main() {
	initDisplay(500, 500, "OpenFTL");
	initOGL();

	setRenderFunction(renderScene);

	startMainLoop();
	return 0;
}
