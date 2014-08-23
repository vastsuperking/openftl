#include "shader.h"

#include <glload/gl_2_0.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static char *SHADER_TYPE_STRINGS[NUM_SHADER_TYPES] = {"vertex", "fragment"};
static GLenum SHADER_TYPE_ENUMS[NUM_SHADER_TYPES] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};

//----- Locally used functions

static GLenum
get_shader_type_enum(ShaderType type) {
	return SHADER_TYPE_ENUMS[type];
}


/*
  Returns a pointer to a char (a string)
  allocated on the heap containing the contents of the file specified with filename
 */

char *
read_shader_source(const char* filename) {
	FILE *input = fopen(filename, "rb");
	long size;
	char *content;

	if(input == NULL) return (NULL);
 
	if(fseek(input, 0, SEEK_END) == -1) return (NULL);
	size = ftell(input);
	if(size == -1) return (NULL);
	if(fseek(input, 0, SEEK_SET) == -1) return (NULL);
 
	content = (char*) malloc((size_t) size +1  ); 
	if(content == NULL) return (NULL);
 
	fread(content, 1, (size_t)size, input);
	if(ferror(input)) {
		free(content);
		return (NULL);
	}
 
	fclose(input);
	content[size] = '\0';
	return (content);
}

char *
get_shader_type_string(ShaderType type) {
	return SHADER_TYPE_STRINGS[type];
}

void
init_shader(Shader *s, ShaderType type, const char *source) {
	GLint status;
	unsigned int handle;
	handle = (unsigned int) glCreateShader(get_shader_type_enum(type));

	glShaderSource(handle, 1, &source, NULL);
	glCompileShader(handle);
	

	glGetShaderiv(handle, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE) {
		char *infoLog;
		char *strType;
		GLint infoLogLength;

		printf("Unable to compile shader!\n");
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &infoLogLength);
		
		/* Get the log */
		infoLog = (char *) malloc(sizeof(GLchar) * (infoLogLength + 1));
		glGetShaderInfoLog(handle, infoLogLength, NULL, infoLog);
		/* Get the type of the shader (vertex, fragment) */
		strType = get_shader_type_string(type);
		printf("Error in %s shader: %s\n", strType, infoLog);

		/* strType is in the data segment, but infolog is on the heap */
		free(infoLog);

		/* Core dump because compile failed */
		assert(0);
	}
	s->handle = handle;
	s->type = type;
}
void
init_shader_from_file(Shader *s, ShaderType type, const char *fileName) {
	char *source = read_shader_source(fileName);
	
	init_shader(s, type, source);
	
	free(source);
}
void
init_program(Program *p, Shader *vs, Shader *fs) {
	GLuint handle = glCreateProgram();
	
	glAttachShader(handle, (*vs).handle);
	glAttachShader(handle, (*fs).handle);

	/* Link the program */
	glLinkProgram(handle);
	
	p->handle = handle;
	p->vertexShader = vs;
	p->fragmentShader = fs;
}


void
init_uniform(Uniform *u, Program *p, ShaderVarType type, const char *name) {
	GLint handle;
	
	handle = glGetUniformLocation(p->handle, name);
	
	u->handle = handle;
	u->type = type;
	u->name = name;
}
void
init_attribute(Attribute *a, Program *p, ShaderVarType type, const char *name) {
	GLint handle;

	handle = glGetAttribLocation(p->handle, name);
	a->handle = handle;
	a->type = type;
	a->name = name;
}

void
clear_attribute(Attribute *a) {
	a->handle = -1;
	a->type = INVALID_SHADER_VAR_TYPE;
	a->name = NULL;
}

void
clear_uniform(Uniform *u) {
	u->handle = -1;
	u->type = INVALID_SHADER_VAR_TYPE;
	u->name = NULL;
}

void
destroy_shader(Shader *s) {
	glDeleteShader(s->handle);
	s->handle = 0;
	s->type = INVALID_SHADER_TYPE;
}
void
destroy_program(Program *p) {
	//Detach shaders
	glDetachShader(p->handle, p->vertexShader->handle);
	glDetachShader(p->handle, p->fragmentShader->handle);
	//Delete the program
	glDeleteProgram(p->handle);
	p->handle = 0;
	p->vertexShader = NULL;
	p->fragmentShader = NULL;
}

void
use_program(Program *p) {
	glUseProgram(p->handle);
}
void
unbind_current_program() {
	glUseProgram(0);
}

void
set_uniform_vec3(Uniform *u, float x, float y, float z) {
	assert(u->type == VEC3);
	glUniform3f(u->handle, x, y, z);
}
void
set_uniform_vec4(Uniform *u, float x, float y, float z, float w) {
	assert(u->type == VEC4);
	glUniform4f(u->handle, x, y, z, w);
}
