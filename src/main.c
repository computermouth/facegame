
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
	
	int x_direction = 1;
	int y_direction = 1;
	
	// primary loop
	while(!ww_window_received_quit_event()) {
		
		// update events
		ww_window_update_events();
		
		// quit
		if(keystate.esc == 1){
			printf("ESC pressed\n");
			ww_window_send_quit_event();
		}
		
		// set animation
	    if(keystate.w == 1 && face->active_animation == 0){
			face->active_animation = 1;
		} else if(keystate.w == 1){
			face->active_animation = 0;
		}
		
		// move x
		face->pad_x = face->pad_x + x_direction;
		if(face->pad_x > 1000){
			x_direction = -1;
		}
		
		if(face->pad_x < 0){
			x_direction = 1;
		}
            					                                  	
		// x_direction = -1
		
		// move y
		face->pad_y = face->pad_y + y_direction;
		if(face->pad_y > 500){
			y_direction = -1;
		}
		if(face->pad_y < 0){
			y_direction = 1;
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
