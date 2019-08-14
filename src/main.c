
// standard library shit
#include <stdio.h>
//~ #include <stdlib.h>
#include <time.h>

// engine shit
#include "ww.h"
#include "states.h"
#include "files.h"

// sprites
#include "dude.h"
#include "sky.h"
#include "ground.h"
#include "grass_decoration.h"

#include "untitled.h"
#include "buttons.h"
#include "selector.h"
#include "title.h"

typedef enum { DOWN, LEFT, RIGHT, UP } direction;
typedef enum { IDLE, WALK } movement;

game_state_t game_state = { 0 };

ww_sprite_t * ground_sprites[10][3];

void inits(){
	
	init_dude();
	init_sky();
	init_ground();
	init_grass_decoration();

	init_untitled();
	init_buttons();
	init_selector();
	init_title();
}

void frees(){
	ww_free_sprite(untitled);
	ww_free_sprite(buttons);
	ww_free_sprite(selector);
	ww_free_sprite(title);
	
	ww_free_sprite(dude);
	ww_free_sprite(sky);
	
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 3; j++){
			ww_free_sprite(ground_sprites[i][j]);
		}
	}
}

void process_top_menu(){
	
	// move left
	if(press_state.lt){
		game_state.top_menu_selected--;
		press_state.lt = 0;
	}
	// wrap left
	if(game_state.top_menu_selected == TOP_MENU_SELECTED_PLAY - 1)
		game_state.top_menu_selected = TOP_MENU_SELECTED_QUIT;
	
	// move right
	if(press_state.rt){
		game_state.top_menu_selected++;
		press_state.rt = 0;
	}
	// wrap right
	if(game_state.top_menu_selected > TOP_MENU_SELECTED_QUIT)
		game_state.top_menu_selected = TOP_MENU_SELECTED_PLAY;
	
	selector->pad_x = 200 * game_state.top_menu_selected;
	
	if(press_state.ent){
		switch(game_state.top_menu_selected){
			case TOP_MENU_SELECTED_PLAY:
				game_state.top_state = TOP_STATE_PLAY;
				break;
			case TOP_MENU_SELECTED_OPTIONS:
				break;
			case TOP_MENU_SELECTED_QUIT:
				game_state.top_state = TOP_STATE_QUIT;
				break;
			default:
				printf("??\n");
				break;
		}
	}
	
	ww_draw_sprite(title);
	ww_draw_sprite(buttons);
	ww_draw_sprite(selector);
	
}

direction dir = DOWN;
movement  mov = IDLE;

int x_prog = 10;
int y_prog = 10;
char ground_slots[10][3];
char anim;

void process_play(){	
		
		char old_anim = anim;
		
		if(keystate.w || keystate.a || keystate.s || keystate.d){
			mov = WALK;
		} else {
			mov = IDLE;
		}
		
		if(keystate.w){
			dir = UP;
			y_prog--;
		}
		
		if(keystate.a){
			dir = LEFT;
			x_prog--;
		}
		
		if(keystate.s){
			dir = DOWN;
			y_prog++;
		}
		
		if(keystate.d){
			dir = RIGHT;
			x_prog++;
		}
		
		if (x_prog == -10) { // moved left
			x_prog = 0;
			
			for(int i = 9; i > 0; i--){
				for(int j = 0; j < 3; j++){
					ground_slots[i][j] = ground_slots[i - 1][j];
					ground_sprites[i][j]->active_animation = ground_slots[i][j] - 1;
				}
			}
			
			for(int i = 0; i < 3; i++){
				ground_slots[0][i] = rand() % 34 - 30;
				if(ground_slots[0][i] < 0){
					ground_slots[0][i] = 0;
				} else {
					ground_sprites[0][i]->active_animation = ground_slots[0][i] - 1;
				}
			}
		}
		
		if (x_prog == 10) { // moved right
			x_prog = 0;
			
			for(int i = 0; i < 9; i++){
				for(int j = 0; j < 3; j++){
					ground_slots[i][j] = ground_slots[i + 1][j];
					ground_sprites[i][j]->active_animation = ground_slots[i][j] - 1;
				}
			}
			
			for(int i = 0; i < 3; i++){
				ground_slots[9][i] = rand() % 34 - 30;
				if(ground_slots[9][i] < 0){
					ground_slots[9][i] = 0;
				} else {
					ground_sprites[9][i]->active_animation = ground_slots[9][i] - 1;
				}
			}
		}
		
		if (y_prog == -10) { // moved up
			y_prog = 0;
			
			for(int j = 2; j > 0; j--){
				for(int i = 0; i < 10; i++){
					ground_slots[i][j] = ground_slots[i][j - 1];
					ground_sprites[i][j]->active_animation = ground_slots[i][j] - 1;
				}
			}
			
			for(int i = 0; i < 10; i++){
				ground_slots[i][0] = rand() % 34 - 30;
				if(ground_slots[i][0] < 0){
					ground_slots[i][0] = 0;
				} else {
					ground_sprites[i][0]->active_animation = ground_slots[i][0] - 1;
				}
			}
		}
		
		if (y_prog == 10) { // moved down
			y_prog = 0;
			
			for(int j = 0; j < 3; j++){
				for(int i = 0; i < 10; i++){
					ground_slots[i][j] = ground_slots[i][j + 1];
					ground_sprites[i][j]->active_animation = ground_slots[i][j] - 1;
				}
			}
			
			for(int i = 0; i < 10; i++){
				ground_slots[i][2] = rand() % 34 - 30;
				if(ground_slots[i][2] < 0){
					ground_slots[i][2] = 0;
				} else {
					ground_sprites[i][2]->active_animation = ground_slots[i][2] - 1;
				}
			}
		}
		
		anim = dir;
		if (mov == WALK){
			anim += 4;
			ground->paused = 0;
		} else {
			ground->paused = 1;
		}
		
		if(old_anim != anim){
			ww_animation_t * active_dude = dude->animations[dude->active_animation];
			active_dude->active_frame = 0;
			active_dude->d_progress = active_dude->delay[0];
		}
		
		dude->active_animation = anim;
		
		ww_draw_sprite(sky);
		ww_draw_sprite(ground);
		
		for(int i = 0; i < 10; i++){
			for(int j = 0; j < 3; j++){
				if (ground_slots[i][j] != 0){
					ww_draw_sprite(ground_sprites[i][j]);
				}
			}
		}
		
		ww_draw_sprite(dude);
	
}

void process_state(){
	
	switch (game_state.top_state){
		case TOP_STATE_IDLE:
			process_top_menu();
			break;
		case TOP_STATE_PLAY:			
			process_play();
			break;
		case TOP_STATE_OPTIONS:
			break;
		case TOP_STATE_QUIT:
			ww_window_send_quit_event();
			break;
	}
	
}

int main( int argc, char * argv[] ) {
	
	// seed random numbers
	srand(time(0));
	
	// initialization
	if(ww_window_create(argc, argv, "Pixarray", 1024, 576)) {
		printf("Closing..\n");
		return 1;
	}
	
	if ( verify_or_create_save(&game_state) != 0 ){
		printf("E: failed to locate or create save file\n");
		return 1;
	} else {
		if ( mload(&game_state) != 0 ){
			return 1;
		}
	}
	
	inits();
	
	// from here
	ground->paused = 1;
	dude->pad_x = 360;
	dude->pad_y = 80;
	anim = dir;
	
	if (mov == WALK)
		anim += 4;
	
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 3; j++){
			ground_sprites[i][j] = ww_clone_sprite(grass_decoration);
			ground_sprites[i][j]->pad_x = i * 100;
			ground_sprites[i][j]->pad_y = (j * 83);
			ground_slots[i][j] = rand() % 34 - 30;
			if (ground_slots[i][j] <= 0){
				ground_slots[i][j] = 0;
			} else {
				ground_sprites[i][j]->active_animation = ground_slots[i][j] - 1;
			}
		}
	}
	// to here, should go somewhere else
	
	// primary loop
	while(!ww_window_received_quit_event()) {
		
		// update events
		ww_window_update_events();
		
		process_state();
		
		// quit
		if(keystate.esc == 1){
			printf("ESC pressed\n");
			ww_window_send_quit_event();
		}
		
		// draw screen
		ww_window_update_buffer();
	}
	
	frees();
	
	// cleanup and exit
	ww_window_destroy();
	return 0;
}
