#ifndef SHADER_H
#define SHADER_H

shader_t   *getTypeString(GLenum shaderType);
shader_t   *createShader(GLenum shaderType, const GLchar *source);
shader_t   *createShaderFromFile(GLenum shaderType, const char *filename);
program_t  *createProgram(shader_t *vertexShader, shader_t *fragmentShader);
void		deleteShader(shader_t *shader);

#endif
