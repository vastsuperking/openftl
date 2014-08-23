#ifndef SHADER_H
#define SHADER_H

typedef enum {
	VERTEX_SHADER = 0,
	FRAGMENT_SHADER,
	NUM_SHADER_TYPES,
	INVALID_SHADER_TYPE
} ShaderType;

typedef enum {
	SVAR_INT = 0,
	SVAR_FLOAT,
	SVAR_VEC2,
	SVAR_VEC3,
	SVAR_VEC4,
	INVALID_SHADER_VAR_TYPE
} ShaderVarType;

typedef struct {
	unsigned int handle;
	ShaderType type;
} Shader;

typedef struct {
	unsigned int handle;
	Shader *vertexShader;
	Shader *fragmentShader;
} Program;

typedef struct {
	int handle;
	ShaderVarType type;
	const char *name;
} Attribute;

typedef struct {
	int handle;
	ShaderVarType type;
	const char *name;
} Uniform;

char *read_shader_source(const char *filename);
char *get_shader_type_string(ShaderType type);
void init_shader(Shader *s, ShaderType type, const char *source);
void init_shader_from_file(Shader *s, ShaderType type, const char *filename);
void init_program(Program *p, Shader *vs, Shader *fs);

void init_uniform(Uniform *u, Program *p, ShaderVarType type, const char *name);
void init_attribute(Attribute *a, Program *p, ShaderVarType type, const char *name);

void clear_attribute(Attribute *a);
void clear_uniform(Uniform *u);

void destroy_shader(Shader *s);
void destroy_program(Program *p);


void use_program(Program *p);
void unbind_current_program();

void set_uniform_vec3(Uniform *u, float x, float y, float z);
void set_uniform_vec4(Uniform *u, float x, float y, float z, float w);

#endif
