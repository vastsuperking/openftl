#ifndef SHADER_STRUCT_H
#define SHADER_STRUCT_H

struct shader {
	GLuint handle;
	GLenum shaderType;
};

typedef struct shader shader_t;

struct program {
	GLuint handle;
	shader_t *vertexShader;
	shader_t *fragmentShader;
};

typedef struct program program_t;

struct attribute {
	GLint location;
	const char *name;
};

typedef struct attribute attribute_t;

struct uniform {
	GLint location;
	const char *name;
};

typedef struct uniform uniform_t;

#endif
