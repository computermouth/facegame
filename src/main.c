
// standard library shit
#include <stdio.h>

// engine shit
#include "ww.h"

// sprites
#include "dude.h"
#include "sky.h"

typedef enum { DOWN, LEFT, RIGHT, UP } direction;
typedef enum { IDLE, WALK } movement;

int main( int argc, char * argv[] ) {
	
	// initialization
	if(ww_window_create(argc, argv, "Pixarray", 1024, 576)) {
		printf("Closing..\n");
		return 1;
	}
	
	init_dude();
	init_sky();
	
	direction dir = DOWN;
	movement  mov = IDLE;
	
	char anim = dir;
	
	if (mov == WALK)
		anim += 4;
	
	dude->pad_x = 360;
	dude->pad_y = 80;
	
	// primary loop
	while(!ww_window_received_quit_event()) {
		
		// update events
		ww_window_update_events();
		
		// quit
		if(keystate.esc == 1){
			printf("ESC pressed\n");
			ww_window_send_quit_event();
		}
		
		char old_anim = anim;
		
		if(keystate.w || keystate.a || keystate.s || keystate.d){
			mov = WALK;
		} else {
			mov = IDLE;
		}
		
		if(keystate.w)
			dir = UP;
		
		if(keystate.a)
			dir = LEFT;
		
		if(keystate.s)
			dir = DOWN;
		
		if(keystate.d)
			dir = RIGHT;
		
		anim = dir;
		if (mov == WALK)
			anim += 4;
		
		if(old_anim != anim){
			ww_animation_t * active_dude = dude->animations[dude->active_animation];
			active_dude->active_frame = 0;
			active_dude->d_progress = active_dude->delay[0];
		}
		
		dude->active_animation = anim;
		ww_draw_sprite(sky);
		ww_draw_sprite(dude);
		
		// draw screen
		ww_window_update_buffer();
	}
	
	ww_free_sprite(dude);
	ww_free_sprite(sky);
	
	// cleanup and exit
	ww_window_destroy();
	return 0;
}
