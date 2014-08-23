#include "renderer.h"

#include <stdio.h>
#include <glload/gl_2_0.h>


void
render_scene() {
	clear_display();
	
	ready_for_rendering();
	
	set_color(1, 0, 0, 1);

	render_quad(-1, -1, 2, 2);
	
	finish_rendering();
	swap_buffers();
}
int
main() {
	init_display(500, 500, "OpenFTL");
	init_OGL();
	set_render_function(render_scene);

	start_main_loop();

	destroy_OGL();
	return 0;
}
