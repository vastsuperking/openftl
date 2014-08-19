#ifndef SHADER_STRUCT_H
#define SHADER_STRUCT_H

struct shader {
	GLuint handle;
	GLenum shaderType;
};
typedef struct shader shader_t;
#endif
