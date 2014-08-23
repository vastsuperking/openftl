#ifndef RENDERER_H
#define RENDERER_H

void init_display(int width, int height, char *name);
void init_OGL();
void destroy_OGL();
void set_render_function(void (*func)(void));
void start_main_loop();
void clear_display();
void swap_buffers();

/*Rendering functions*/

void ready_for_rendering();
void finish_rendering();

void set_color(float r, float g, float b, float a);

void render_quad(float x, float y, float width, float height);

#endif
