
// standard library shit
#include <stdio.h>
//~ #include <stdlib.h>
#include <time.h>

// engine shit
#include "ww.h"
#include "ww_font.h"

// supporting
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
#include "xp_bit.h"

#include "untitled.h"
#include "buttons.h"
#include "selector.h"
#include "title.h"

#define WINDOW_WIDTH  1024
#define WINDOW_HEIGHT 576

typedef enum { DOWN, LEFT, RIGHT, UP } direction;
typedef enum { IDLE, WALK } movement;

game_state_t game_state = { 0 };

ww_sprite_t * ground_sprites[10][3];
ww_sprite_t * xp_slots[3][3];
ww_sprite_t * xp_sprites[3][3];

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

ww_sprite_t * gamename = NULL;
ww_sprite_t * alpha1 = NULL;
ww_sprite_t * alpha2 = NULL;

ww_sprite_t * text_level_up = NULL;
ww_sprite_t * text_xp_gain = NULL;
ww_sprite_t * text_victory = NULL;
ww_sprite_t * text_defeat = NULL;

ww_sprite_t * ok = NULL;

void inits(){
	
	ok = ww_new_sprite(XP_BIT);
	ww_scale_sprite(ok);
	ok->pad_x = WINDOW_WIDTH - ok->width;
	ww_scale_sprite(ok);
	
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
	
	gamename = ww_new_sprite_from_string("GAME", (ww_rgba_t){127, 127, 255});
	gamename->scale = 16.0;
	ww_scale_sprite(gamename);
	gamename->pad_x = (WINDOW_WIDTH  / 2) - (gamename->width  / 2);
	gamename->pad_y = (WINDOW_HEIGHT / 4) - (gamename->height / 2);
	
	alpha1 = ww_new_sprite_from_string("ABCDEFGHIJKLMNOPQRS", (ww_rgba_t){255, 127, 0});
	alpha1->scale = 9.0;
	ww_scale_sprite(alpha1);
	
	alpha2 = ww_new_sprite_from_string("TUVWXYZ0123456789.!", (ww_rgba_t){255, 127, 0});
	alpha2->scale = 9.0;
	ww_scale_sprite(alpha2);
	alpha2->pad_y = (alpha1->height) * 1.25;
	
	text_level_up = ww_new_sprite_from_string("LEVEL UP!!!", (ww_rgba_t){0, 255, 127});
	text_level_up->scale = 10.0;
	ww_scale_sprite(text_level_up);
	text_level_up->pad_x = (WINDOW_WIDTH / 2    ) - (text_level_up->width  / 2);
	text_level_up->pad_y = (WINDOW_HEIGHT * 7/8 ) - (text_level_up->height / 2);
	
	text_xp_gain = ww_new_sprite_from_string("XP", (ww_rgba_t){255, 255, 0});
	text_xp_gain->scale = 8.0;
	ww_scale_sprite(text_xp_gain);
	text_xp_gain->pad_x = (WINDOW_WIDTH / 2) - (text_xp_gain->width / 2);
	text_xp_gain->pad_y = text_xp_gain->height;
	
	text_victory = ww_new_sprite_from_string("VICTORY!!!", (ww_rgba_t){0, 255, 127});
	text_victory->scale = 10.0;
	ww_scale_sprite(text_victory);
	text_victory->pad_x = (WINDOW_WIDTH  / 2 ) - (text_victory->width  / 2);
	text_victory->pad_y = (WINDOW_HEIGHT / 8 ) - (text_victory->height / 2);
	
	text_defeat = ww_new_sprite_from_string("DEFEAT", (ww_rgba_t){127, 0, 255});
	text_defeat->scale = 10.0;
	ww_scale_sprite(text_defeat);
	text_defeat->pad_x = (WINDOW_WIDTH / 2  ) - (text_defeat->width  / 2);
	text_defeat->pad_y = (WINDOW_HEIGHT / 8 ) - (text_defeat->height / 2);
}

void frees(){
	
	free(dude);
	free(sky);
	free(ground);
	free(grass_decoration);
	
	free(untitled);
	free(buttons);
	free(selector);
	free(title);
	
	free(pause_menu);
	free(map_event);
	free(spiral);
	
	free(gamename);
	free(alpha1);
	free(alpha2);
	free(text_level_up);
	free(text_xp_gain);
	free(text_victory);
	free(text_defeat);
	
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 3; j++){
			free(ground_sprites[i][j]);
		}
	}
	
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			free(xp_sprites[i][j]);
		}
	}
	
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			free(xp_slots[i][j]);
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
	ww_draw_sprite(gamename);
	ww_draw_sprite(alpha1);
	ww_draw_sprite(alpha2);
}

int process_play_menu_esc_previous_frame_value = 1;
int player_flash_rate = 30;
int draw_player = 1;

ww_sprite_t * pos_label = NULL;
ww_sprite_t * lvl_label = NULL;
ww_sprite_t *  hp_label = NULL;
ww_sprite_t * atk_label = NULL;
ww_sprite_t *  xp_label = NULL;

void process_play_menu(){
	
	if (pos_label == NULL){
		char tmp[50];
		
		sprintf(tmp, "XYPOS: %02d-%02d", game_state.play_state.player.x_pos, game_state.play_state.player.y_pos );
		pos_label = ww_new_sprite_from_string(tmp, (ww_rgba_t){0, 0, 0});
		pos_label->scale = 6.0;
		ww_scale_sprite(pos_label);
		pos_label->pad_x = (WINDOW_WIDTH * 3 / 4) - (pos_label->width /  2);
		pos_label->pad_y = (WINDOW_HEIGHT * 7 / 8) + (pos_label->height /  2);
		
		sprintf(tmp, "LVL: %02d", game_state.play_state.player.level );
		lvl_label = ww_new_sprite_from_string(tmp, (ww_rgba_t){0, 0, 0});
		lvl_label->scale = 6.0;
		ww_scale_sprite(lvl_label);
		lvl_label->pad_x = lvl_label->scale * 8;
		lvl_label->pad_y = lvl_label->scale * 8;
		
		sprintf(tmp, "HP : %02d / %02d", game_state.play_state.player.hp, game_state.play_state.player.max_hp );
		hp_label = ww_new_sprite_from_string(tmp, (ww_rgba_t){0, 0, 0});
		hp_label->scale = 6.0;
		ww_scale_sprite(hp_label);
		hp_label->pad_x = hp_label->scale * 8;
		hp_label->pad_y = hp_label->scale * 16;
		
		sprintf(tmp, "ATK: %d-%d-%d-%d", game_state.play_state.player.atk[0], game_state.play_state.player.atk[1], game_state.play_state.player.atk[2], game_state.play_state.player.atk[3] );
		atk_label = ww_new_sprite_from_string(tmp, (ww_rgba_t){0, 0, 0});
		atk_label->scale = 6.0;
		ww_scale_sprite(atk_label);
		atk_label->pad_x = atk_label->scale * 8;
		atk_label->pad_y = atk_label->scale * 24;
		
		int totalxp = 0;
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++)
				totalxp += game_state.play_state.player.exp[i][j];
		
		sprintf(tmp, "EXP: %d / 9", totalxp );
		xp_label = ww_new_sprite_from_string(tmp, (ww_rgba_t){0, 0, 0});
		xp_label->scale = 6.0;
		ww_scale_sprite(xp_label);
		xp_label->pad_x = xp_label->scale * 8;
		xp_label->pad_y = xp_label->scale * 32;
		
	}
	
	if ( (ipstate.back || ipstate.c_str) && process_play_menu_esc_previous_frame_value == 0) {
		game_state.play_state.play_state_activity = PLAY_STATE_ROAM;
		process_play_menu_esc_previous_frame_value = 1;
		
		free(pos_label);
		free(lvl_label);
		free( hp_label);
		free(atk_label);
		free( xp_label);
		
		pos_label = NULL;
		lvl_label = NULL;
		 hp_label = NULL;
		atk_label = NULL;
		 xp_label = NULL;
		
		return;
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
	
	ww_draw_sprite(pos_label);
	ww_draw_sprite(lvl_label);
	ww_draw_sprite( hp_label);
	ww_draw_sprite(atk_label);
	ww_draw_sprite( xp_label);
	
	
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
			game_state.play_state.play_state_activity = PLAY_STATE_EVENT;
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

void generate_event(){
	int event_x = rand() % MAP_WIDTH;
	int event_y = rand() % MAP_HEIGHT;
	
	while ( // don't put an event on the player, or on existing event
		(event_x == game_state.play_state.player.x_pos && 
		event_y == game_state.play_state.player.y_pos ) ||
		game_state.play_state.map[event_x][event_y] == 1
	){
		event_x = rand() % MAP_WIDTH;
		event_y = rand() % MAP_HEIGHT;
	}
	
	game_state.play_state.map[event_x][event_y] = 1;
}

void process_battle_init(){
	
	// only show the spiral until it ends
	static int spiral_runs = 0;
	if (spiral_runs < 1){
		ww_draw_sprite(spiral);
		if(spiral->animations[0].active_frame == SPIRAL_ANIMATION_0_FRAME_COUNT - 1)
			spiral_runs = 1;
		return;
	}
	
	//~ ww_window_s *window_p = (ww_window_s*) window;
	
	char tmp[40];
	sprintf(tmp, "HP: %02d / %02d", game_state.play_state.player.hp, game_state.play_state.player.max_hp);
	
	battler_t *player_battler = &game_state.play_state.event.battle.player_battler;
	player_battler->bt_sprite = ww_new_sprite(DUDE),
	player_battler->hp_sprite = ww_new_sprite_from_string(tmp, (ww_rgba_t){255, 255, 255}),
	player_battler->level     = game_state.play_state.player.level,
	player_battler->max_hp    = game_state.play_state.player.max_hp,
	player_battler->hp        = game_state.play_state.player.hp,
	player_battler->speed     = game_state.play_state.player.speed,
	player_battler->tmp_speed = game_state.play_state.player.speed,
	player_battler->baseatk   = game_state.play_state.player.baseatk,
	player_battler->basedef   = game_state.play_state.player.basedef,
	player_battler->atk       = game_state.play_state.player.atk,
	player_battler->def       = game_state.play_state.player.def,
	player_battler->bt_sprite->active_animation = DUDE_WALK_RIGHT_INDEX;
	player_battler->bt_sprite->pad_x = 0;
	
	ww_scale_sprite(player_battler->bt_sprite);
	player_battler->bt_sprite->pad_y = (WINDOW_HEIGHT / 2) - (player_battler->bt_sprite->height / 2);
	
	player_battler->hp_sprite->scale = 6.0;
	ww_scale_sprite(player_battler->hp_sprite);
	player_battler->hp_sprite->pad_x = player_battler->hp_sprite->scale * 5;
	player_battler->hp_sprite->pad_y = (WINDOW_HEIGHT * 7/8) - (player_battler->hp_sprite->height / 2);
	
	
	battler_t *enemy_battler = &game_state.play_state.event.battle.enemy_battler; // TODO, actually generate enemy
	enemy_battler->bt_sprite = ww_new_sprite(DUDE),
	enemy_battler->level     = game_state.play_state.player.level,
	enemy_battler->max_hp    = game_state.play_state.player.max_hp / 2,
	enemy_battler->hp        = enemy_battler->max_hp,
	
	sprintf(tmp, "HP: %02d / %02d", (game_state.play_state.player.hp / 2), (game_state.play_state.player.max_hp / 2));
	enemy_battler->hp_sprite = ww_new_sprite_from_string(tmp, (ww_rgba_t){255, 255, 255}),
	
	enemy_battler->speed     = game_state.play_state.player.speed + 45,
	enemy_battler->tmp_speed = game_state.play_state.player.speed,
	enemy_battler->baseatk   = game_state.play_state.player.baseatk,
	enemy_battler->basedef   = game_state.play_state.player.basedef,
	enemy_battler->atk       = game_state.play_state.player.atk,
	enemy_battler->def       = game_state.play_state.player.def,
	enemy_battler->bt_sprite->active_animation = DUDE_WALK_LEFT_INDEX;
	
	ww_scale_sprite(enemy_battler->bt_sprite);
	enemy_battler->bt_sprite->pad_y = (WINDOW_HEIGHT / 2) - (enemy_battler->bt_sprite->height / 2);
	enemy_battler->bt_sprite->pad_x = WINDOW_WIDTH - enemy_battler->bt_sprite->width;
	
	enemy_battler->hp_sprite->scale = 6.0;
	ww_scale_sprite(enemy_battler->hp_sprite);
	enemy_battler->hp_sprite->pad_y = (WINDOW_HEIGHT * 7/8) - (enemy_battler->hp_sprite->height / 2);
	enemy_battler->hp_sprite->pad_x = WINDOW_WIDTH - enemy_battler->hp_sprite->width - enemy_battler->hp_sprite->scale * 5;
	
	game_state.play_state.event.battle.battle_state_activity = BATTLE_STATE_BATTLE;
	spiral_runs = 0;
	
}

void process_battle_end(){
	
	battle_state_t * battle_state = &game_state.play_state.event.battle;
	play_state_t   *   play_state = &game_state.play_state;
	
	if(battle_state->player_battler.bt_sprite != NULL) free(battle_state->player_battler.bt_sprite);
	if(battle_state->player_battler.hp_sprite != NULL) free(battle_state->player_battler.hp_sprite);
	if(battle_state->enemy_battler.bt_sprite != NULL)  free(battle_state->enemy_battler.bt_sprite);
	if(battle_state->enemy_battler.hp_sprite != NULL)  free(battle_state->enemy_battler.hp_sprite);
	
	battle_state->player_battler.bt_sprite = NULL;
	battle_state->player_battler.hp_sprite = NULL;
	battle_state->enemy_battler.bt_sprite = NULL;
	battle_state->enemy_battler.hp_sprite = NULL;
	
	play_state->player.hp     = battle_state->player_battler.hp;
	play_state->player.max_hp = battle_state->player_battler.max_hp;
	
	battle_state->battle_state_activity    = 0;
	battle_state->player_battler.bt_sprite = NULL;
	battle_state->player_battler.level     = 0;
	battle_state->player_battler.max_hp    = 0;
	battle_state->player_battler.hp        = 0;
	battle_state->player_battler.speed     = 0;
	battle_state->player_battler.tmp_speed = 0;
	battle_state->player_battler.baseatk   = 0;
	battle_state->player_battler.basedef   = 0;
	battle_state->player_battler.atk       = NULL;
	battle_state->player_battler.def       = NULL;
	battle_state->enemy_battler.bt_sprite  = NULL;
	battle_state->enemy_battler.level      = 0;
	battle_state->enemy_battler.max_hp     = 0;
	battle_state->enemy_battler.hp         = 0;
	battle_state->enemy_battler.speed      = 0;
	battle_state->enemy_battler.tmp_speed  = 0;
	battle_state->enemy_battler.baseatk    = 0;
	battle_state->enemy_battler.basedef    = 0;
	battle_state->enemy_battler.atk        = NULL;
	battle_state->enemy_battler.def        = NULL;
	
	battle_state->battle_state_activity = BATTLE_STATE_INIT;
	
	if (play_state->player.hp > 0){
		play_state->event.event_state_activity = EVENT_STATE_XPUP;
		//~ play_state->play_state_activity = PLAY_STATE_ROAM;
	} else
		play_state->event.event_state_activity = EVENT_STATE_REST;
		
}

void process_weapon_find(){
	
	static uint32_t new_weapon[4] = {0, 0, 0, 0};
	static uint32_t new_weapon_total = -1;
	static ww_sprite_t * text_new_weapon    = NULL;
	static ww_sprite_t * text_cur_weapon    = NULL;
	static ww_sprite_t * text_choose_weapon = NULL;
	
	if (new_weapon_total == -1){
		int32_t weapon_randomizer = 0;
		for(int i = 0; i < game_state.play_state.player.level / 5; i++)
			weapon_randomizer += (rand() % 6) - (rand() % 4);
		
		printf("randomizer -- %d\n", weapon_randomizer);
		
		new_weapon_total = (game_state.play_state.player.level + weapon_randomizer) % 37;

		while(new_weapon_total > 36)
			new_weapon_total -= (game_state.play_state.player.level / 6) + 1;
		
		for(int i = 0; i < new_weapon_total; i++){
			int index = rand() % 4;
			if(new_weapon[index] != 9)
				new_weapon[index]++;
			else
				i--;
		}
		
		char tmp[20];
		sprintf(tmp, "NEW: %d-%d-%d-%d", new_weapon[0], new_weapon[1], new_weapon[2], new_weapon[3]);
		text_new_weapon = ww_new_sprite_from_string(tmp, (ww_rgba_t){255, 255, 255});
		text_new_weapon->scale = 6.0;
		ww_scale_sprite(text_new_weapon);
		text_new_weapon->pad_x = (WINDOW_WIDTH  /   2) - text_new_weapon->width  / 2;
		text_new_weapon->pad_y = (WINDOW_HEIGHT * 3/5) - text_new_weapon->height / 2;
		
		uint32_t * cur_weapon = game_state.play_state.player.atk;
		sprintf(tmp, "CUR: %d-%d-%d-%d", cur_weapon[0], cur_weapon[1], cur_weapon[2], cur_weapon[3]);
		text_cur_weapon = ww_new_sprite_from_string(tmp, (ww_rgba_t){255, 255, 255});
		text_cur_weapon->scale = 6.0;
		ww_scale_sprite(text_cur_weapon);
		text_cur_weapon->pad_x = (WINDOW_WIDTH  /   2) - text_cur_weapon->width  / 2;
		text_cur_weapon->pad_y = (WINDOW_HEIGHT * 4/5) - text_cur_weapon->height / 2;
		
		text_choose_weapon = ww_new_sprite_from_string("CHOOSE A WEAPON:", (ww_rgba_t){127, 255, 0});
		text_choose_weapon->scale = 10.0;
		ww_scale_sprite(text_choose_weapon);
		text_choose_weapon->pad_x = (WINDOW_WIDTH  /   2) - text_choose_weapon->width  / 2;
		text_choose_weapon->pad_y = text_choose_weapon->height;
	}
	
	ww_draw_sprite(text_new_weapon);
	ww_draw_sprite(text_cur_weapon);
	ww_draw_sprite(text_choose_weapon);
	
	if (istate.cfrm){
		game_state.play_state.player.atk[0] = new_weapon[0];
		game_state.play_state.player.atk[1] = new_weapon[1];
		game_state.play_state.player.atk[2] = new_weapon[2];
		game_state.play_state.player.atk[3] = new_weapon[3];
		
		free(text_new_weapon);
		free(text_cur_weapon);
		free(text_choose_weapon);
		
		text_new_weapon    = NULL;
		text_cur_weapon    = NULL;
		text_choose_weapon = NULL;
		
		new_weapon_total = -1;
		new_weapon[0] = 0;
		new_weapon[1] = 0;
		new_weapon[2] = 0;
		new_weapon[3] = 0;
		
		game_state.play_state.event.event_state_activity = EVENT_STATE_NONE;
		game_state.play_state.play_state_activity = PLAY_STATE_ROAM;
	}
	
}

void process_xp_gain(){
	
	static int xp_x = 1;
	static int xp_y = 1;
	
	static int does_level_up = 0;
	
	int old_xx = xp_x;
	int old_xy = xp_y;
	
	       int phases[6]     = {  8, 12, 17, 27, 40, 120 };
	static int tmp_phases[6] = {  8, 12, 17, 27, 40, 120 };
	       int counts[6]     = { 10,  9,  7,  4,  2,   1 };
	static int tmp_counts[6] = { 10,  9,  7,  4,  2,   1 };
	static int mode = 0;
	
	tmp_phases[mode]--;
	if(tmp_phases[mode] == 0){
		tmp_phases[mode] = phases[mode];
		tmp_counts[mode]--;

		if(tmp_counts[mode] == 0)
			mode++;
		
		while ( // move new xp bit every $phases frames
			mode != 5 && (
				game_state.play_state.player.exp[xp_x][xp_y] ||
				((old_xx == xp_x) && (old_xy == xp_y))
			)
		){
			xp_x = rand() % 3;
			xp_y = rand() % 3;
		}
	}
	
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			ww_draw_sprite(xp_slots[i][j]);
			if (game_state.play_state.player.exp[i][j])
				ww_draw_sprite(xp_sprites[i][j]);
		}
	}
	
	if (!does_level_up)
		ww_draw_sprite(xp_sprites[xp_x][xp_y]);
	
	if(mode == 5 && !does_level_up ){
		game_state.play_state.player.exp[xp_x][xp_y] = 1;
	}
	
	if(mode == 6){
		game_state.play_state.event.event_state_activity = EVENT_STATE_NONE;
		game_state.play_state.play_state_activity = PLAY_STATE_ROAM;
		mode = 0;
		tmp_counts[0] = counts[0];
		tmp_counts[1] = counts[1];
		tmp_counts[2] = counts[2];
		tmp_counts[3] = counts[3];
		tmp_counts[4] = counts[4];
		tmp_counts[5] = counts[5];
		tmp_phases[0] = phases[0];
		tmp_phases[1] = phases[1];
		tmp_phases[2] = phases[2];
		
		if (does_level_up){
			for(int i = 0; i < 3; i++)
				for(int j = 0; j < 3; j++)
					game_state.play_state.player.exp[i][j] = 0;
			game_state.play_state.player.level  +=  1;
			
			int old_max_hp = game_state.play_state.player.max_hp;
			game_state.play_state.player.max_hp  = game_state.play_state.player.level * 1.5;
			game_state.play_state.player.hp     += (game_state.play_state.player.max_hp - old_max_hp);
			does_level_up = 0;
		}
	}
	
	if ( mode == 5 && (
	//~ if (
		(// top row
			game_state.play_state.player.exp[0][0] &&
			game_state.play_state.player.exp[0][1] &&
			game_state.play_state.player.exp[0][2]
		) ||
		(// middle row
			game_state.play_state.player.exp[1][0] &&
			game_state.play_state.player.exp[1][1] &&
			game_state.play_state.player.exp[1][2]
		) ||
		(// bottom row
			game_state.play_state.player.exp[2][0] &&
			game_state.play_state.player.exp[2][1] &&
			game_state.play_state.player.exp[2][2]
		) ||
		(// left column
			game_state.play_state.player.exp[0][0] &&
			game_state.play_state.player.exp[1][0] &&
			game_state.play_state.player.exp[2][0]
		) ||
		(// middle column
			game_state.play_state.player.exp[0][1] &&
			game_state.play_state.player.exp[1][1] &&
			game_state.play_state.player.exp[2][1]
		) ||
		(// right column
			game_state.play_state.player.exp[0][2] &&
			game_state.play_state.player.exp[1][2] &&
			game_state.play_state.player.exp[2][2]
		) ||
		(// tl -> br
			game_state.play_state.player.exp[0][0] &&
			game_state.play_state.player.exp[1][1] &&
			game_state.play_state.player.exp[2][2]
		) ||
		(// tr -> bl
			game_state.play_state.player.exp[0][2] &&
			game_state.play_state.player.exp[1][1] &&
			game_state.play_state.player.exp[2][0]
		) )
		) {
		
		does_level_up = 1;
	}
	
	if (does_level_up)
		ww_draw_sprite(text_level_up);
	
	ww_draw_sprite(text_xp_gain);
	
}

void process_battle_battle(){
		
	static int player_atk_stick = 0;
	static int enemy_atk_stick = 0;
	static int fight_over_wait = 180;
	
	battle_state_t *battle_state = &game_state.play_state.event.battle;
	
	// end battle
	if (battle_state->player_battler.hp <= 0) {
		if (fight_over_wait != 0){
			ww_draw_sprite(text_defeat);
			fight_over_wait--;
			battle_state->player_battler.hp = 0;
			goto draw_sprites;
		}
	} else if (battle_state->enemy_battler.hp <= 0) {
		if (fight_over_wait != 0){
			ww_draw_sprite(text_victory);
			fight_over_wait--;
			battle_state->enemy_battler.hp = 0;
			goto draw_sprites;
		}
	}
	
	if (fight_over_wait == 0) {		
		game_state.play_state.event.battle.battle_state_activity = BATTLE_STATE_END;
		player_atk_stick = 0;
		enemy_atk_stick = 0;
		fight_over_wait = 180;
		return;
	}
	
	// reset positions from attacks
	battler_t *enemy_battler = &game_state.play_state.event.battle.enemy_battler;
	
	if (player_atk_stick != 0)
		player_atk_stick--;
	else
		battle_state->player_battler.bt_sprite->pad_x = 0;
		
	if (enemy_atk_stick != 0)
		enemy_atk_stick--;
	else {
		enemy_battler->bt_sprite->pad_x = WINDOW_WIDTH - enemy_battler->bt_sprite->width;
	}
			
	// perform attack
	battle_state->player_battler.tmp_speed--;
	if (battle_state->player_battler.tmp_speed == 0) {
		battle_state->player_battler.bt_sprite->pad_x += 50;
		int dmg_index = rand() % 4;
		battle_state->enemy_battler.hp -= battle_state->player_battler.atk[dmg_index];
		battle_state->player_battler.tmp_speed = battle_state->player_battler.speed;
		player_atk_stick = 30;
		
		char tmp[20];
		sprintf(tmp, "HP: %02d / %02d", battle_state->enemy_battler.hp, battle_state->enemy_battler.max_hp);
		free(battle_state->enemy_battler.hp_sprite);
		battle_state->enemy_battler.hp_sprite = ww_new_sprite_from_string(tmp, (ww_rgba_t){255, 255, 255});
		battle_state->enemy_battler.hp_sprite->scale = 6.0;
		ww_scale_sprite(battle_state->enemy_battler.hp_sprite);
		battle_state->enemy_battler.hp_sprite->pad_x = WINDOW_WIDTH - battle_state->enemy_battler.hp_sprite->width - battle_state->enemy_battler.hp_sprite->scale * 5;
		battle_state->enemy_battler.hp_sprite->pad_y = (WINDOW_HEIGHT * 7/8) - (battle_state->enemy_battler.hp_sprite->height / 2);
		
		if (battle_state->enemy_battler.hp <= 0)
			goto draw_sprites;
	}
	
	battle_state->enemy_battler.tmp_speed--;
	if (battle_state->enemy_battler.tmp_speed == 0) {
		battle_state->enemy_battler.bt_sprite->pad_x -= 50;
		int dmg_index = rand() % 4;
		battle_state->player_battler.hp -= battle_state->enemy_battler.atk[dmg_index];
		battle_state->enemy_battler.tmp_speed = battle_state->enemy_battler.speed;
		enemy_atk_stick = 30;
		
		char tmp[20];
		sprintf(tmp, "HP: %02d / %02d", battle_state->player_battler.hp, battle_state->player_battler.max_hp);
		free(battle_state->player_battler.hp_sprite);
		battle_state->player_battler.hp_sprite = ww_new_sprite_from_string(tmp, (ww_rgba_t){255, 255, 255});
		battle_state->player_battler.hp_sprite->scale = 6.0;
		ww_scale_sprite(battle_state->player_battler.hp_sprite);
		battle_state->player_battler.hp_sprite->pad_x = battle_state->player_battler.hp_sprite->scale * 5;
		battle_state->player_battler.hp_sprite->pad_y = (WINDOW_HEIGHT * 7/8) - (battle_state->player_battler.hp_sprite->height / 2);
	}
	
	draw_sprites:
	
	ww_draw_sprite(battle_state->player_battler.bt_sprite);
	ww_draw_sprite(battle_state->player_battler.hp_sprite);
	
	ww_draw_sprite(battle_state->enemy_battler.bt_sprite);
	ww_draw_sprite(battle_state->enemy_battler.hp_sprite);
	
}

ww_sprite_t * text_resting = NULL;
ww_sprite_t * sleeper = NULL;
ww_sprite_t * sleeper_hp = NULL;
ww_sprite_t * sleeperz1 = NULL;
ww_sprite_t * sleeperz2 = NULL;

void process_rest(){
	
	uint32_t *max_hp = &game_state.play_state.player.max_hp;
	int32_t  *cur_hp = &game_state.play_state.player.hp;
	
	static int hp_gain_wait = 120;
	
	// setup
	if (text_resting == NULL) {
		text_resting = ww_new_sprite_from_string("RESTING", (ww_rgba_t){127, 0, 255});
		text_resting->scale = 10.0;
		ww_scale_sprite(text_resting);
		text_resting->pad_x = (WINDOW_WIDTH / 2  ) - (text_resting->width  / 2);
		text_resting->pad_y = (WINDOW_HEIGHT / 8 ) - (text_resting->height / 2);
		
		sleeper = ww_new_sprite(DUDE);
		sleeper->pad_x = (WINDOW_WIDTH / 2  ) - (sleeper->width  / 2);
		sleeper->pad_y = (WINDOW_HEIGHT / 2 ) - (sleeper->height / 2);
		
		sleeperz1 = ww_new_sprite_from_string("Z", (ww_rgba_t){0, 0xBB, 255});
		sleeperz1->scale = 6.0;
		ww_scale_sprite(sleeperz1);
		sleeperz1->pad_x = sleeper->width + sleeper->pad_x + sleeperz1->width  * 2;
		sleeperz1->pad_y = sleeper->pad_y + sleeperz1->height * 2;
		
		sleeperz2 = ww_new_sprite_from_string("Z", (ww_rgba_t){0, 0xBB, 255});
		sleeperz2->scale = 10.0;
		ww_scale_sprite(sleeperz2);
		sleeperz2->pad_x = sleeperz1->pad_x + sleeperz2->width;
		sleeperz2->pad_y = sleeperz1->pad_y - sleeperz2->height;
		
		char tmp[40];
		sprintf(tmp, "HP: %02u / %02u", *cur_hp, *max_hp);
		sleeper_hp = ww_new_sprite_from_string(tmp, (ww_rgba_t){255, 255, 255});
		sleeper_hp->scale = 10.0;
		ww_scale_sprite(sleeper_hp);
		sleeper_hp->pad_x = (WINDOW_WIDTH / 2    ) - (sleeper_hp->width  / 2);
		sleeper_hp->pad_y = (WINDOW_HEIGHT * 7/8 ) - (sleeper_hp->height / 2);
		
	}
	
	hp_gain_wait--;
	if(hp_gain_wait == 0){
		*cur_hp = *cur_hp + 1;
		hp_gain_wait = 120;
		free(sleeper_hp);
		
		char tmp[40];
		sprintf(tmp, "HP: %02d / %02d", *cur_hp, *max_hp);
		sleeper_hp = ww_new_sprite_from_string(tmp, (ww_rgba_t){255, 255, 255});
		sleeper_hp->scale = 10.0;
		ww_scale_sprite(sleeper_hp);
		sleeper_hp->pad_x = (WINDOW_WIDTH / 2    ) - (sleeper_hp->width  / 2);
		sleeper_hp->pad_y = (WINDOW_HEIGHT * 7/8 ) - (sleeper_hp->height / 2);
	}
	
	ww_draw_sprite(text_resting);
	ww_draw_sprite(sleeper);
	ww_draw_sprite(sleeperz1);
	if(*cur_hp % 2 == 1)
		ww_draw_sprite(sleeperz2);
	ww_draw_sprite(sleeper_hp);
	
	if ( // hp is max, or hp is half max and any key is pressed
		(*cur_hp == *max_hp) ||
		(
			(*cur_hp >= *max_hp / 2) &&
				(
					istate.c_str ||
					istate.c_sel ||
					istate.c_up  ||
					istate.c_dn  ||
					istate.c_lt  ||
					istate.c_rt  ||
					istate.c_a   ||
					istate.c_b   ||
					istate.c_x   ||
					istate.c_y
				)
		)
	){
		hp_gain_wait = 120;
		
		free(text_resting);
		free(sleeper     );
		free(sleeper_hp  );
		free(sleeperz1   );
		free(sleeperz2   );
		text_resting = NULL;
		sleeper = NULL;
		sleeper_hp = NULL;
		sleeperz1 = NULL;
		sleeperz2 = NULL;
		
		game_state.play_state.event.event_state_activity = EVENT_STATE_NONE;
		game_state.play_state.play_state_activity = PLAY_STATE_ROAM;
	}
	
}

void process_battle(){
	
	battle_state_t battle_state = game_state.play_state.event.battle;
	
	switch (battle_state.battle_state_activity){
		case BATTLE_STATE_INIT:
			process_battle_init();
			break;
		case BATTLE_STATE_BATTLE:
			process_battle_battle();	
			break;
		case BATTLE_STATE_END:
			process_battle_end();
			break;
	}
	
	// reset spiral_runs after a finished battle
}

void determine_event(){
	
	int odds_max    =  0;
	int odds_battle = 20;
	int odds_xp     =  3;
	int odds_rest   =  7;
	int odds_weapon = 10;
	
	// battle encounter
	odds_max += odds_battle;
	
	// xp encounter
	odds_max += odds_xp;
	
	// rest encounter
	if (game_state.play_state.player.hp <= game_state.play_state.player.max_hp / 3)
		odds_max += odds_rest;
	else
		odds_rest = 0;
	
	// weapon encounter
	int weapon_power =
		game_state.play_state.player.atk[0] +
		game_state.play_state.player.atk[1] +
		game_state.play_state.player.atk[2] +
		game_state.play_state.player.atk[3];
	if (weapon_power < game_state.play_state.player.level - 1)
		odds_max += odds_weapon;
	else
		odds_weapon = 0;
	
	// TODO -- EVENT_STORY
	
	int event = rand() % odds_max;
	
	if      (event < odds_battle)
		game_state.play_state.event.event_state_activity = EVENT_STATE_BATTLE;
	else if (event < odds_battle + odds_xp)
		game_state.play_state.event.event_state_activity = EVENT_STATE_XPUP;
	else if (event < odds_battle + odds_xp + odds_rest)
		game_state.play_state.event.event_state_activity = EVENT_STATE_REST;
	else if (event < odds_battle + odds_xp + odds_rest + odds_weapon)
		game_state.play_state.event.event_state_activity = EVENT_STATE_WEAPONUP;
	
	//~ switch (game_state.play_state.event.event_state_activity){
		//~ case EVENT_STATE_BATTLE:
			//~ printf("found battle -- event: %d\n", event);
			//~ break;
		//~ case EVENT_STATE_XPUP:
			//~ printf("found xp -- event: %d\n", event);
			//~ break;
		//~ case EVENT_STATE_REST:
			//~ printf("found rest -- event: %d\n", event);
			//~ break;
		//~ case EVENT_STATE_WEAPONUP:
			//~ printf("found weapon -- event: %d\n", event);
			//~ break;
		//~ case EVENT_STATE_NONE:
			//~ printf("found none??? -- event: %d\n", event);
			//~ break;
	//~ }
	
	game_state.play_state.map[game_state.play_state.player.x_pos][game_state.play_state.player.y_pos] = 0;
	generate_event();
	
}

void process_event(){

	switch (game_state.play_state.event.event_state_activity){
		case EVENT_STATE_NONE:
			determine_event(); // fall through to process chosen event
		case EVENT_STATE_BATTLE:
			process_battle();
			break;
		case EVENT_STATE_XPUP:
			process_xp_gain();
			break;
		case EVENT_STATE_REST:
			process_rest();
			break;
		case EVENT_STATE_WEAPONUP:
			process_weapon_find();
			break;
	}
	
}

void process_play(){

	switch (game_state.play_state.play_state_activity){
		case PLAY_STATE_ROAM:
			process_roam();
			break;
		case PLAY_STATE_MENU:
			process_play_menu();
			break;
		case PLAY_STATE_EVENT:
			process_event();
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
	
	ww_window_s *window_p = (ww_window_s*) window;
	
	// TODO -- reset temp stats (player hp, starting xp)
	game_state.play_state.player.level     = 3;
	game_state.play_state.player.max_hp    = 4;
	//~ game_state.play_state.player.hp        = 4;
	game_state.play_state.player.hp        = 1;
	//~ game_state.play_state.player.speed     = 120;
	game_state.play_state.player.speed     = 30;
	game_state.play_state.player.baseatk   = 1;
	game_state.play_state.player.basedef   = 1;
	game_state.play_state.player.atk[0]    = 1;
	game_state.play_state.player.atk[1]    = 1;
	game_state.play_state.player.atk[2]    = 1;
	game_state.play_state.player.atk[3]    = 0;
	game_state.play_state.player.def[0]    = 0;
	game_state.play_state.player.def[1]    = 0;
	game_state.play_state.player.def[2]    = 0;
	game_state.play_state.player.def[3]    = 1;
	//~ game_state.play_state.player.exp[0][0] = 0;
	game_state.play_state.player.exp[0][0] = 1;
	game_state.play_state.player.exp[0][1] = 0;
	//~ game_state.play_state.player.exp[0][2] = 0;
	game_state.play_state.player.exp[0][2] = 1;
	game_state.play_state.player.exp[1][0] = 0;
	game_state.play_state.player.exp[1][1] = 0;
	game_state.play_state.player.exp[1][2] = 0;
	//~ game_state.play_state.player.exp[2][0] = 0;
	game_state.play_state.player.exp[2][0] = 1;
	game_state.play_state.player.exp[2][1] = 0;
	//~ game_state.play_state.player.exp[2][2] = 0;
	game_state.play_state.player.exp[2][2] = 1;
	game_state.play_state.player.x_pos     = MAP_WIDTH  / 2;
	game_state.play_state.player.y_pos     = MAP_HEIGHT / 2;
	game_state.play_state.player.sub_x_pos = 240;
	game_state.play_state.player.sub_y_pos = 240;
	
	game_state.options_menu_state.volume   = 5;
	game_state.options_menu_state.scale    = window_p->ww_scale;
	
	game_state.play_state.event.event_state_activity = EVENT_STATE_NONE;
	
	game_state.play_state.event.battle.battle_state_activity    = 0;
	game_state.play_state.event.battle.player_battler.bt_sprite = NULL;
	game_state.play_state.event.battle.player_battler.level     = 0;
	game_state.play_state.event.battle.player_battler.max_hp    = 0;
	game_state.play_state.event.battle.player_battler.hp        = 0;
	game_state.play_state.event.battle.player_battler.speed     = 0;
	game_state.play_state.event.battle.player_battler.baseatk   = 0;
	game_state.play_state.event.battle.player_battler.basedef   = 0;
	game_state.play_state.event.battle.player_battler.atk       = NULL;
	game_state.play_state.event.battle.player_battler.def       = NULL;
	game_state.play_state.event.battle.enemy_battler.bt_sprite  = NULL;
	game_state.play_state.event.battle.enemy_battler.level      = 0;
	game_state.play_state.event.battle.enemy_battler.max_hp     = 0;
	game_state.play_state.event.battle.enemy_battler.hp         = 0;
	game_state.play_state.event.battle.enemy_battler.speed      = 0;
	game_state.play_state.event.battle.enemy_battler.baseatk    = 0;
	game_state.play_state.event.battle.enemy_battler.basedef    = 0;
	game_state.play_state.event.battle.enemy_battler.atk        = NULL;
	game_state.play_state.event.battle.enemy_battler.def        = NULL;
	
	// magic number for event density 1/36 units
	//~ for(int i = 0; i < 18; i++){
	for(int i = 0; i < 500; i++){
		generate_event();
	}
	
	// defaults on load
	ground->paused = 1;
	dude->pad_x = 360;
	dude->pad_y = 80;
	anim = dir;
	
	if (mov == WALK)
		anim += 4;
	
	// populate grass doodads
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
	
	int offset[3] = { -1, 0 , 1 };
	// xp bits
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			xp_sprites[i][j] = ww_new_sprite(XP_BIT);
			xp_sprites[i][j]->pad_x = (WINDOW_WIDTH  / 2) - (xp_sprites[i][j]->width  / 2) + (offset[i] * 128);
			xp_sprites[i][j]->pad_y = (WINDOW_HEIGHT / 2) - (xp_sprites[i][j]->height / 2) + (offset[j] * 128);
		}
	}
	
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			xp_slots[i][j] = ww_new_sprite(XP_BIT);
			xp_slots[i][j]->pad_x = (WINDOW_WIDTH  / 2) - (xp_slots[i][j]->width  / 2) + (offset[i] * 128)- (xp_slots[i][j]->width  / 7);
			xp_slots[i][j]->pad_y = (WINDOW_HEIGHT / 2) - (xp_slots[i][j]->height / 2) + (offset[j] * 128)- (xp_slots[i][j]->height / 7);
			xp_slots[i][j]->animations[0].frames[0].polys[0].color[0] = 127;
			xp_slots[i][j]->animations[0].frames[0].polys[0].color[1] = 127;
			xp_slots[i][j]->animations[0].frames[0].polys[0].color[2] = 127;
		}
	}
	
}

int main( int argc, char * argv[] ) {
	
	// seed random numbers
	srand(time(0));
	
	// initialization
	if(ww_window_create(argc, argv, "Pixarray", WINDOW_WIDTH, WINDOW_HEIGHT)) {
		printf("Closing..\n");
		return 1;
	}
	
	//~ if ( verify_or_create_save(&game_state) != 0 ){
		//~ printf("E: failed to locate or create save file\n");
		//~ return 1;
	//~ } else {
		//~ if ( mload(&game_state) != 0 ){
			//~ return 1;
		//~ }
	//~ }
	
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
