#include <stdio.h>
#include <stdlib.h>
#include <glload/gl_2_0.h>
#include "shader_struct.h"

char *
readFileContents(const char* filename) {
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
getTypeString(GLenum shaderType) {
	char *strShaderType = NULL;
	switch(shaderType) {
	case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
//	case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
	case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
	}
	return (strShaderType);
}

shader_t *
createShader(GLenum shaderType, const GLchar *source) {
	GLuint handle;

	GLint status;
	GLint infoLogLength;
	GLchar *infoLog;
	
	shader_t *shader;

	handle = glCreateShader(shaderType);

	glShaderSource(handle, 1, &source, NULL);
	glCompileShader(handle);

	glGetShaderiv(handle, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE) {
		printf("Unable to compile shader!\n");
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &infoLogLength);

		infoLog = malloc(sizeof(GLchar) * (infoLogLength + 1));
		glGetShaderInfoLog(handle, infoLogLength, NULL, infoLog);
		printf("Error in %s shader: %s\n", getTypeString(shaderType), infoLog);
		free(infoLog);
	}

	shader = malloc(sizeof(shader_t));
	(*shader).handle = handle;
	(*shader).shaderType = shaderType;
	return (shader);
}
program_t *
createProgram(shader_t *vs, shader_t *fs) {
	program_t *program;
	GLuint programID;

	programID = glCreateProgram();
	
	glAttachShader(programID, (*vs).handle);
	glAttachShader(programID, (*fs).handle);

	/* Link the program */
	glLinkProgram(programID);
	
	program = malloc(sizeof(program_t));
	(*program).handle = programID;
	(*program).vertexShader = vs;
	(*program).fragmentShader = fs;
	return (program);
}

shader_t *
createShaderFromFile(GLenum shaderType, const char *filename) {
	const char *source = readFileContents(filename);
	return (createShader(shaderType, source));
}

void
deleteShader(shader_t *shader) {
	shader_t s = *shader;
	glDeleteShader(s.handle);
	free(shader);
}
void
deleteProgram(program_t *program) {
	glDeleteProgram(program->handle);
	free(program);
}

uniform_t *
getUniform(program_t *program, const char *name) {
	GLint handle;
	uniform_t *uniform;

	handle = glGetUniformLocation((*program).handle, name);
	
	uniform = malloc(sizeof(uniform_t));
	(*uniform).location = handle;
	(*uniform).name = name;
	return (uniform);
}

attribute_t *
getAttribute(program_t *program, const char *name) {
	GLint handle;
	attribute_t *attribute;
	
	handle = glGetAttribLocation((*program).handle, name);
	attribute = malloc(sizeof(attribute_t));
	(*attribute).location = handle;
	(*attribute).name = name;
	return (attribute);
}
