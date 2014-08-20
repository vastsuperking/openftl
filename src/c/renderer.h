#ifndef RENDERER_H
#define RENDERER_H

void initDisplay(int width, int height, char *name);
void initOGL();
void destroyOGL();
void setRenderFunction(void (*func)(void));
void startMainLoop();
void clearDisplay();
void swapBuffers();
#endif
