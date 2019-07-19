
// standard library shit
#include <stdio.h>

// engine shit
#include "ww.h"

// sprites
#include "face.h"

int main( int argc, char * argv[] ) {
	
	// initialization
	if(ww_window_create(argc, argv, "Pixarray", 1024, 576)) {
		printf("Closing..\n");
		return 1;
	}
	
	init_face();
	
	// primary loop
	while(!ww_window_received_quit_event()) {
		
		// update events
		ww_window_update_events();
		
		if(keystate.esc == 1){
			printf("ESC pressed\n");
		}
		
		ww_draw_sprite(face);
		
		// draw screen
		ww_window_update_buffer();
	}
	
	ww_free_sprite(face);
	
	// cleanup and exit
	ww_window_destroy();
	return 0;
}
