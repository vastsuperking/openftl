#include "renderer.h"
#include "shader.h"

#include <glload/gl_2_0.h>
#include <glload/gl_load.h>
#include <GL/freeglut.h>
#include <stdio.h>




static Shader *fragShader;
static Shader *vertexShader;
static Program *program;

static Attribute *vertPosAttrib;
static Uniform *colorUni;

//Temporary values, will move to vec4 or color struct
static float colorRed;
static float colorBlue;
static float colorGreen;
static float colorAlpha;

void
init_display(int width, int height, char *name) {
	int argc = 1;
	int loadTest;
	char *myargv[1];

	myargv[0] = name;
	glutInit(&argc, myargv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	//glutInitContextVersion(MAJOR_CONTEXT_VERSION, MINOR_CONTEXT_VERSION);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow(name);

	loadTest = ogl_LoadFunctions();
	if (loadTest == ogl_LOAD_FAILED) printf("Loading opengl function pointers failed!");
}

void
init_OGL() {
	program = malloc(sizeof(Program));
	fragShader = malloc(sizeof(Shader));
	vertexShader = malloc(sizeof(Shader));

	vertPosAttrib = malloc(sizeof(Attribute));
	colorUni = malloc(sizeof(Uniform));

	init_shader_from_file(fragShader, FRAGMENT_SHADER, "fragment.frag");
	init_shader_from_file(vertexShader, VERTEX_SHADER, "vertex.vert");
	init_program(program, fragShader, vertexShader);
	init_attribute(vertPosAttrib, program, SVAR_VEC2, "vertPos");
	init_uniform(colorUni, program, SVAR_VEC4, "color");
	
	//Set default color to white
	colorRed = 1;
	colorGreen = 1;
	colorBlue = 1;
	colorAlpha = 1;
}

void
destroy_OGL() {
	destroy_shader(fragShader);
	destroy_shader(vertexShader);
	destroy_program(program);
	clear_attribute(vertPosAttrib);
	clear_uniform(colorUni);

	free(program);

	free(fragShader);
	free(vertexShader);

	free(vertPosAttrib);
	free(colorUni);
}

void
set_render_function(void (*func)(void)) {
	glutDisplayFunc(func);
}

void
start_main_loop() {
	glutMainLoop();
}

void
clear_display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void
swap_buffers() {
	glutSwapBuffers();
}

/*----Rendering Functions----*/

void
ready_for_rendering() {
	use_program(program);
}

void
finish_rendering() {
	unbind_current_program();
}

void
set_color(float r, float g, float b, float a) {
	colorRed = r;
	colorGreen = g;
	colorBlue = b;
	colorAlpha = a;
}

void
render_quad(float x, float y, float width, float height) {
	GLfloat vertices[] = {x + width, y + height, 
						  x, y + height,
						  x, y,
						  x + width, y};
	GLubyte indices[] = {0, 1, 2, 0, 2, 3};

	//Set color variable before rendering quad
	set_uniform_vec4(colorUni, colorRed, colorGreen, colorBlue, colorAlpha);

	glEnableVertexAttribArray(vertPosAttrib->handle);
	glVertexAttribPointer(vertPosAttrib->handle, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);
	glDisableVertexAttribArray(vertPosAttrib->handle);
}
