#include "renderer.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static Texture *wood;
static Texture *spaceship;



/*Utility functions*/
void
init_texture_png_resource(Texture *t, char *resource) {
	char *prefix = "../resources/";
	char result[strlen(resource) + strlen(prefix) + 1];
	//Clear the string
	result[0] = '\0';

	strcat(result, prefix);
	strcat(result, resource);

	init_texture_png(t, result);
}

/* Main functions */

void
init_textures() {
	wood = malloc(sizeof(Texture));
	spaceship = malloc(sizeof(Texture));

	init_texture_png_resource(wood, "wood_test.png");
	init_texture_png_resource(spaceship, "ships/blueship1.png");
}
void
cleanup_textures() {
	destroy_texture(wood);
	free(wood);
	free(spaceship);
}


void
render_scene() {
	clear_display();
	
	ready_for_rendering();
	
	/*set_color(1, 0, 0, 1);*/
	set_texture(wood);

	render_quad(-1, -1, 2, 2);

	set_texture(spaceship);

	render_quad(-0.5, -1, 1, 2);

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

