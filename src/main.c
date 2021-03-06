
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
#include "pause_menu.h"
#include "map_event.h"
#include "spiral.h"
#include "wiper.h"

#include "untitled.h"
#include "buttons.h"
#include "selector.h"
#include "title.h"

typedef enum { DOWN, LEFT, RIGHT, UP } direction;
typedef enum { IDLE, WALK } movement;

game_state_t game_state = { 0 };

ww_sprite_t * ground_sprites[10][3];

ww_sprite_t * dude = NULL;
ww_sprite_t * sky = NULL;
ww_sprite_t * ground = NULL;
ww_sprite_t * grass_decoration = NULL;
ww_sprite_t * untitled = NULL;
ww_sprite_t * buttons = NULL;
ww_sprite_t * selector = NULL;
ww_sprite_t * title = NULL;
ww_sprite_t * pause_menu = NULL;
ww_sprite_t * map_event = NULL;
ww_sprite_t * spiral = NULL;

void inits(){
	
	dude = ww_new_sprite(DUDE);
	sky = ww_new_sprite(SKY);
	ground = ww_new_sprite(GROUND);
	grass_decoration = ww_new_sprite(GRASS_DECORATION);

	untitled = ww_new_sprite(UNTITLED);
	buttons = ww_new_sprite(BUTTONS);
	selector = ww_new_sprite(SELECTOR);
	title = ww_new_sprite(TITLE);
	
	pause_menu = ww_new_sprite(PAUSE_MENU);
	map_event = ww_new_sprite(MAP_EVENT);
	spiral = ww_new_sprite(SPIRAL);
}

void frees(){
	free(untitled);
	free(buttons);
	free(selector);
	free(title);
	
	free(dude);
	free(sky);
	free(spiral);
	
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 3; j++){
			free(ground_sprites[i][j]);
		}
	}
}

void process_top_menu(){
	
	// move left
	if(ipstate.c_lt){
		game_state.top_menu_selected--;
		ipstate.c_lt = 0;
	}
	// wrap left
	if(game_state.top_menu_selected == TOP_MENU_SELECTED_PLAY - 1)
		game_state.top_menu_selected = TOP_MENU_SELECTED_QUIT;
	
	// move right
	if(ipstate.c_rt){
		game_state.top_menu_selected++;
		ipstate.c_rt = 0;
	}
	// wrap right
	if(game_state.top_menu_selected > TOP_MENU_SELECTED_QUIT)
		game_state.top_menu_selected = TOP_MENU_SELECTED_PLAY;
	
	selector->pad_x = 200 * game_state.top_menu_selected;
	
	if(ipstate.cfrm){
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

int process_play_menu_esc_previous_frame_value = 1;
int player_flash_rate = 30;
int draw_player = 1;

void process_play_menu(){
	
	if ( (ipstate.back || ipstate.c_str) && process_play_menu_esc_previous_frame_value == 0) {
		game_state.play_state.play_state_activity = PLAY_STATE_ROAM;
		process_play_menu_esc_previous_frame_value = 1;
	}
	
	ww_draw_sprite(pause_menu);
	
	for(int i = 0; i < MAP_WIDTH; i++){
		for(int j = 0; j < MAP_HEIGHT; j++){
			if(game_state.play_state.map[i][j] == 1){
				map_event->pad_x = 544 + (16 * i);
				map_event->pad_y = 32  + (16 * j);
				ww_draw_sprite(map_event);
			}
		}
	}
	
	// draw flashing player dot
	if (draw_player){
		map_event->pad_x = 544 + (16 * game_state.play_state.player.x_pos);
		map_event->pad_y = 32  + (16 * game_state.play_state.player.y_pos);
		ww_draw_sprite(map_event);
	}
	
	if(player_flash_rate <= 0){
		player_flash_rate = 30 - abs(player_flash_rate);
		
		if(draw_player == 0){
			draw_player = 1;
		} else {
			draw_player = 0;
		}
	}
	
	player_flash_rate-= ww_frames_passed();
	
	process_play_menu_esc_previous_frame_value = (istate.back | istate.c_str | istate.c_sel);
	
}

direction dir = DOWN;
movement  mov = IDLE;

int x_prog = 10;
int y_prog = 10;
char ground_slots[10][3];
char anim;

int process_roam_esc_previous_frame_value = 1;

void process_roam(){
		
		char old_anim = anim;
		mov = IDLE;
		
		if( (ipstate.c_sel || ipstate.c_str) && process_roam_esc_previous_frame_value == 0){
			game_state.play_state.play_state_activity = PLAY_STATE_MENU;
			process_roam_esc_previous_frame_value = 1;
			
			process_play_menu();
			return;
		}
		
		if(istate.c_up){
			mov = WALK;
			dir = UP;
		}
		
		if(istate.c_lt){
			mov = WALK;
			dir = LEFT;
		}
		
		if(istate.c_dn){
			mov = WALK;
			dir = DOWN;
		}
		
		if(istate.c_rt){
			mov = WALK;
			dir = RIGHT;
		}
		
		// move ground doodads
		// move player
		if (mov == WALK){
			switch (dir) {
				case UP:
					y_prog -= ww_frames_passed();
					game_state.play_state.player.sub_y_pos-=10;
					break;
				case LEFT:
					x_prog -= ww_frames_passed();
					game_state.play_state.player.sub_x_pos-=10;
					break;
				case DOWN:
					y_prog += ww_frames_passed();
					game_state.play_state.player.sub_y_pos+=10;
					break;
				case RIGHT:
					x_prog += ww_frames_passed();
					game_state.play_state.player.sub_x_pos+=10;
					break;
			}
		}
		
		// handle ground doodads
		if (x_prog <= -10) { // moved left
			x_prog = x_prog % 10;
			
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
		
		if (x_prog >= 10) { // moved right
			x_prog = x_prog % 10;
			
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
		
		if (y_prog <= -10) { // moved up
			y_prog = y_prog % 10;
			
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
		
		if (y_prog >= 10) { // moved down
			y_prog = y_prog % 10;
			
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
		
		// handle player
		if (game_state.play_state.player.sub_x_pos <=   0){ //left
			game_state.play_state.player.sub_x_pos = 479;
			game_state.play_state.player.x_pos -= ww_frames_passed();
			if(game_state.play_state.player.x_pos < 0)
				game_state.play_state.player.x_pos = MAP_WIDTH - 1;
		}
		
		if (game_state.play_state.player.sub_x_pos >= 480){ //right
			game_state.play_state.player.sub_x_pos = 1;
			game_state.play_state.player.x_pos += ww_frames_passed();
			if(game_state.play_state.player.x_pos > MAP_WIDTH - 1)
				game_state.play_state.player.x_pos = 0;
		}
		if (game_state.play_state.player.sub_y_pos <=   0){ //up
			game_state.play_state.player.sub_y_pos = 479;
			game_state.play_state.player.y_pos -= ww_frames_passed();
			if(game_state.play_state.player.y_pos < 0)
				game_state.play_state.player.y_pos = MAP_HEIGHT - 1;
		}
		if (game_state.play_state.player.sub_y_pos >= 480){ //down
			game_state.play_state.player.sub_y_pos = 1;
			game_state.play_state.player.y_pos += ww_frames_passed();
			if(game_state.play_state.player.y_pos > MAP_HEIGHT - 1)
				game_state.play_state.player.y_pos = 0;
		}
		
		if (game_state.play_state.map[game_state.play_state.player.x_pos][game_state.play_state.player.y_pos]){
			game_state.play_state.play_state_activity = PLAY_STATE_BATTLE;
		}
				
		anim = dir;
		if (mov == WALK){
			anim += 4;
			ground->paused = 0;
		} else {
			ground->paused = 1;
		}
		
		if(old_anim != anim){
			ww_animation_t * active_dude = &dude->animations[dude->active_animation];
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
	
	process_roam_esc_previous_frame_value = istate.back | istate.c_sel;
	
}

void process_battle(){
	ww_draw_sprite(spiral);
}

void process_play(){	

	switch (game_state.play_state.play_state_activity){
		case PLAY_STATE_BATTLE:
			process_battle();
			break;
		case PLAY_STATE_DEFUP:
			break;
		case PLAY_STATE_DISTRACTION:
			break;
		case PLAY_STATE_EVENT:
			break;
		case PLAY_STATE_LEVELUP:
			break;
		case PLAY_STATE_MENU:
			process_play_menu();
			break;
		case PLAY_STATE_ROAM:
			process_roam();
			break;
		case PLAY_STATE_WEAPONUP:
			break;
	}

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

void game_prop_init(){
	
	game_state.play_state.player.level     = 1;
	game_state.play_state.player.max_hp    = 5;
	game_state.play_state.player.hp        = 5;
	game_state.play_state.player.speed     = 1;
	game_state.play_state.player.baseatk   = 1;
	game_state.play_state.player.basedef   = 1;
	game_state.play_state.player.atk[0]    = 1;
	game_state.play_state.player.atk[1]    = 1;
	game_state.play_state.player.atk[2]    = 1;
	game_state.play_state.player.atk[3]    = 1;
	game_state.play_state.player.def[0]    = 1;
	game_state.play_state.player.def[1]    = 1;
	game_state.play_state.player.def[2]    = 1;
	game_state.play_state.player.def[3]    = 1;
	game_state.play_state.player.exp[0]    = 0;
	game_state.play_state.player.exp[1]    = 0;
	game_state.play_state.player.exp[2]    = 0;
	game_state.play_state.player.exp[3]    = 0;
	game_state.play_state.player.exp[4]    = 0;
	game_state.play_state.player.exp[5]    = 0;
	game_state.play_state.player.exp[6]    = 0;
	game_state.play_state.player.exp[7]    = 0;
	game_state.play_state.player.exp[8]    = 0;
	game_state.play_state.player.x_pos     = MAP_WIDTH  / 2;
	game_state.play_state.player.y_pos     = MAP_HEIGHT / 2;
	game_state.play_state.player.sub_x_pos = 240;
	game_state.play_state.player.sub_y_pos = 240;
	game_state.options_menu_state.volume   = 5;
	game_state.options_menu_state.scale    = SC_ONE;
	
	// magic number for event density 1/36 units
	for(int i = 0; i < 18; i++){
		int event_x = rand() % MAP_WIDTH;
		int event_y = rand() % MAP_HEIGHT;
		
		if( 
			( event_x == game_state.play_state.player.x_pos && 
			event_y == game_state.play_state.player.y_pos ) ||
			game_state.play_state.map[event_x][event_y] == 1
		){
			// don't put an event on the player
			// don't put an event where there is already an event
			i--;
			continue;
		}
		
		game_state.play_state.map[event_x][event_y] = 1;
	}
	
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
	game_prop_init();
	
	// primary loop
	while(!ww_window_received_quit_event()) {
		
		// update events
		ww_window_update_events();
		
		process_state();
		
		// draw screen
		ww_window_update_buffer();
	}
	
	frees();
	
	// cleanup and exit
	ww_window_destroy();
	return 0;
}
