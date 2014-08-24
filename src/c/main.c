#include "renderer.h"

#include <stdlib.h>
#include <stdio.h>
#include <glload/gl_2_0.h>


static Texture *wood;

void
init_textures() {
	Texture *w = malloc(sizeof(Texture));
	init_texture_png(w, "./../resources/wood_test.png");
	wood = w;
}
void
cleanup_textures() {
	destroy_texture(wood);
	free(wood);
}


void
render_scene() {
	clear_display();
	
	ready_for_rendering();
	
	set_color(1, 0, 0, 1);
	set_texture(wood);

	render_quad(-1, -1, 2, 2);
	
	finish_rendering();
	swap_buffers();
}
int
main() {
	init_display(500, 500, "OpenFTL");
	init_OGL();
	init_textures();

	set_render_function(render_scene);

	start_main_loop();


	cleanup_textures();
	destroy_OGL();
	return 0;
}
