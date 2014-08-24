#include "renderer.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <glload/gl_2_0.h>

static Texture *wood;



/*Utility functions*/
void
init_texture_png_resource(Texture *t, char *resource) {
	char *prefix = "../resources/";
	char new[strlen(resource) + strlen(prefix) + 1];
	//Clear the string
	new[0] = '\0';

	strcat(new, prefix);
	strcat(new, resource);

	init_texture_png(t, new);
}

/* Main functions */

void
init_textures() {
	Texture *w = malloc(sizeof(Texture));
	init_texture_png_resource(w, "wood_test.png");
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

