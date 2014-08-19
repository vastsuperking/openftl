#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include "shader_struct.h"

#define MAX_LINES 300
#define LINE_SIZE

char*
readFileContents(const char* filename) {
	FILE *input = fopen(filename, "rb");
	long size;
	char *content;

	if(input == NULL) return (NULL);
 
	if(fseek(input, 0, SEEK_END) == -1) return (NULL);
	size = ftell(input);
	if(size == -1) return (NULL);
	if(fseek(input, 0, SEEK_SET) == -1) return (NULL);
 
	/*if using c-compiler: dont cast malloc's return value*/
	content = (char*) malloc( (size_t) size +1  ); 
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

char*
getTypeString(GLenum shaderType) {
	char *strShaderType = NULL;
	switch(shaderType) {
	case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
	case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
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
		printf("Unable to compile shader!");
		glGetShadferiv(handle, GL_INFO_LOG_LENGTH, &infoLogLength);

		infoLog = malloc(sizeof(GLchar) * (infoLogLength + 1));
		glGetShaderInfoLog(handle, infoLogLength, NULL, infoLog);
		printf("Error in %s: %s", getTypeString(shaderType), infoLog);
		free(infoLog);
	}

	shader = malloc(sizeof(shader_t));
	return (shader);
}

shader_t *
createShaderFromFile(GLenum shaderType, const char *filename) {
	const char *source = readFileContents(filename);
	return (createShader(shaderType, source));
}

void
deleteShader(shader_t *shader) {
	free(shader);
}



