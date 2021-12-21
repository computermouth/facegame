
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

typedef enum { DOWN, LEFT, RIGHT, UP } direction;
typedef enum { IDLE, WALK } movement;

game_state_t game_state = { 0 };

ww_sprite_t * ground_sprites[10][3];
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
	
	gamename = ww_new_sprite_from_string("GAME", (ww_rgba_t){127, 127, 255});
	gamename->scale = 16.0;
	ww_scale_sprite(gamename);
	printf("gamename->width: %d\n", gamename->width);
	gamename->pad_x = (1024 / 2) - (gamename->width  * gamename->scale)  / 2;
	gamename->pad_y = (576 / 4)  - (gamename->height * gamename->scale)  / 2;
	
	alpha1 = ww_new_sprite_from_string("ABCDEFGHIJKLMNOPQRS", (ww_rgba_t){255, 127, 0});
	alpha1->scale = 9.0;
	ww_scale_sprite(alpha1);	
	
	alpha2 = ww_new_sprite_from_string("TUVWXYZ0123456789.!", (ww_rgba_t){255, 127, 0});
	alpha2->scale = 9.0;
	ww_scale_sprite(alpha2);
	alpha2->pad_y = (alpha1->height * alpha1->scale) * 1.5;
}

void frees(){
	free(untitled);
	free(buttons);
	free(selector);
	free(title);
	
	free(dude);
	free(sky);
	free(spiral);
	free(ground);
	free(grass_decoration);
	
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
	
	
	
	ww_window_s *window_p = (ww_window_s*) window;
	
	battler_t *player_battler = &game_state.play_state.battle.player_battler;
	player_battler->sprite    = ww_new_sprite(DUDE),
	player_battler->level     = game_state.play_state.player.level,
	player_battler->max_hp    = game_state.play_state.player.max_hp,
	player_battler->hp        = game_state.play_state.player.hp,
	player_battler->speed     = game_state.play_state.player.speed,
	player_battler->tmp_speed = game_state.play_state.player.speed,
	player_battler->baseatk   = game_state.play_state.player.baseatk,
	player_battler->basedef   = game_state.play_state.player.basedef,
	player_battler->atk       = game_state.play_state.player.atk,
	player_battler->def       = game_state.play_state.player.def,
	player_battler->sprite->active_animation = DUDE_WALK_RIGHT_INDEX;
	player_battler->sprite->pad_x = 0;
	
	ww_scale_sprite(player_battler->sprite);
	player_battler->sprite->pad_y = (window_p->ww_default_height / 2) - (player_battler->sprite->height / 2);
	
	battler_t *enemy_battler = &game_state.play_state.battle.enemy_battler; // TODO, actually generate enemy
	enemy_battler->sprite    = ww_new_sprite(DUDE),
	enemy_battler->level     = game_state.play_state.player.level,
	enemy_battler->max_hp    = game_state.play_state.player.max_hp / 2,
	enemy_battler->hp        = game_state.play_state.player.hp / 2,
	enemy_battler->speed     = game_state.play_state.player.speed + 45,
	enemy_battler->tmp_speed = game_state.play_state.player.speed,
	enemy_battler->baseatk   = game_state.play_state.player.baseatk,
	enemy_battler->basedef   = game_state.play_state.player.basedef,
	enemy_battler->atk       = game_state.play_state.player.atk,
	enemy_battler->def       = game_state.play_state.player.def,
	enemy_battler->sprite->active_animation = DUDE_WALK_LEFT_INDEX;
	
	ww_scale_sprite(enemy_battler->sprite);
	enemy_battler->sprite->pad_x = window_p->ww_default_width - enemy_battler->sprite->width;
	enemy_battler->sprite->pad_y = (window_p->ww_default_height / 2) - (enemy_battler->sprite->height / 2);
	
	game_state.play_state.battle.battle_state_activity = BATTLE_STATE_BATTLE;
	spiral_runs = 0;
	
}

void process_battle_end(){
	
	battle_state_t battle_state = game_state.play_state.battle;
	
	if(battle_state.player_battler.sprite != NULL) free(battle_state.player_battler.sprite);
	if(battle_state.enemy_battler.sprite != NULL)  free(battle_state.enemy_battler.sprite);
	
	game_state.play_state.player.hp = battle_state.player_battler.hp;
	
	// TODO -- if player.hp == 0 -- PLAY_STATE_REST
	
	game_state.play_state.battle.battle_state_activity    = 0;
	game_state.play_state.battle.player_battler.sprite    = NULL;
	game_state.play_state.battle.player_battler.level     = 0;
	game_state.play_state.battle.player_battler.max_hp    = 0;
	game_state.play_state.battle.player_battler.hp        = 0;
	game_state.play_state.battle.player_battler.speed     = 0;
	game_state.play_state.battle.player_battler.tmp_speed = 0;
	game_state.play_state.battle.player_battler.baseatk   = 0;
	game_state.play_state.battle.player_battler.basedef   = 0;
	game_state.play_state.battle.player_battler.atk       = NULL;
	game_state.play_state.battle.player_battler.def       = NULL;
	game_state.play_state.battle.enemy_battler.sprite    = NULL;
	game_state.play_state.battle.enemy_battler.level     = 0;
	game_state.play_state.battle.enemy_battler.max_hp    = 0;
	game_state.play_state.battle.enemy_battler.hp        = 0;
	game_state.play_state.battle.enemy_battler.speed     = 0;
	game_state.play_state.battle.enemy_battler.tmp_speed = 0;
	game_state.play_state.battle.enemy_battler.baseatk   = 0;
	game_state.play_state.battle.enemy_battler.basedef   = 0;
	game_state.play_state.battle.enemy_battler.atk       = NULL;
	game_state.play_state.battle.enemy_battler.def       = NULL;
	
	game_state.play_state.map[game_state.play_state.player.x_pos][game_state.play_state.player.y_pos] = 0;
	generate_event();
	
	game_state.play_state.battle.battle_state_activity = BATTLE_STATE_INIT;
	game_state.play_state.play_state_activity = PLAY_STATE_ROAM;
}

void process_xp_gain(){
	
	static int xp_x = 1;
	static int xp_y = 1;
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
			mode != 6 && (
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
			if (game_state.play_state.player.exp[i][j])
				ww_draw_sprite(xp_sprites[i][j]);
		}
	}
	
	ww_draw_sprite(xp_sprites[xp_x][xp_y]);
	
	if(mode == 6){
		game_state.play_state.player.exp[xp_x][xp_y] = 1;
		game_state.play_state.battle.battle_state_activity = BATTLE_STATE_END;
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
	}
	
	if (
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
		)
	) {
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++)
				game_state.play_state.player.exp[i][j] = 0;
		
		game_state.play_state.player.level  +=  1;
		game_state.play_state.player.hp     += 10;
		game_state.play_state.player.max_hp += 10;
	}
	
}

void process_battle_battle(){
	
	battle_state_t *battle_state = &game_state.play_state.battle;
	
	// end battle
	if (battle_state->player_battler.hp == 0) {
		game_state.play_state.battle.battle_state_activity = BATTLE_STATE_END;
		printf("player dies\n");
		return;
	} else if (battle_state->enemy_battler.hp == 0) {
		game_state.play_state.battle.battle_state_activity = BATTLE_STATE_XP;
		printf("enemy dies\n");
		return;
	}
	
	static int player_atk_stick = 0;
	static int enemy_atk_stick = 0;
	
	// reset positions from attacks
	ww_window_s *window_p = (ww_window_s*) window;
	if (player_atk_stick != 0)
		player_atk_stick--;
	else
		battle_state->player_battler.sprite->pad_x = 0;
		
	if (enemy_atk_stick != 0)
		enemy_atk_stick--;
	else
		battle_state->enemy_battler.sprite->pad_x = window_p->ww_default_width - battle_state->enemy_battler.sprite->width;
	
	// perform attack
	battle_state->player_battler.tmp_speed--;
	if (battle_state->player_battler.tmp_speed == 0) {
		battle_state->player_battler.sprite->pad_x += 50;
		int dmg_index = rand() % 4;
		battle_state->enemy_battler.hp -= battle_state->player_battler.atk[dmg_index];
		battle_state->player_battler.tmp_speed = battle_state->player_battler.speed;
		player_atk_stick = 30;
	}
	
	battle_state->enemy_battler.tmp_speed--;
	if (battle_state->enemy_battler.tmp_speed == 0) {
		battle_state->enemy_battler.sprite->pad_x -= 50;
		int dmg_index = rand() % 4;
		battle_state->player_battler.hp -= battle_state->enemy_battler.atk[dmg_index];
		battle_state->enemy_battler.tmp_speed = battle_state->enemy_battler.speed;
		enemy_atk_stick = 30;
	}
	
	ww_draw_sprite(battle_state->player_battler.sprite);
	ww_draw_sprite(battle_state->enemy_battler.sprite);
	
}

void process_battle(){
	
	battle_state_t battle_state = game_state.play_state.battle;
	
	switch (battle_state.battle_state_activity){
		case BATTLE_STATE_INIT:
			process_battle_init();
			break;
		case BATTLE_STATE_BATTLE:
			process_battle_battle();	
			break;
		case BATTLE_STATE_XP:
			process_xp_gain();
			break;
		case BATTLE_STATE_END:
			process_battle_end();
			break;
	}
	
	// reset spiral_runs after a finished battle
}

void process_play(){	

	switch (game_state.play_state.play_state_activity){
		case PLAY_STATE_BATTLE:
			process_battle();
			break;
		case PLAY_STATE_REST:
			break;
		case PLAY_STATE_EVENT:
			break;
		case PLAY_STATE_MENU:
			process_play_menu();
			break;
		case PLAY_STATE_ROAM:
			process_roam();
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
	
	game_state.play_state.player.level     = 1;
	game_state.play_state.player.max_hp    = 5;
	game_state.play_state.player.hp        = 5;
	game_state.play_state.player.speed     = 120;
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
	game_state.play_state.player.exp[0][0] = 0;
	game_state.play_state.player.exp[0][1] = 0;
	game_state.play_state.player.exp[0][2] = 0;
	game_state.play_state.player.exp[1][0] = 0;
	game_state.play_state.player.exp[1][1] = 0;
	game_state.play_state.player.exp[1][2] = 0;
	game_state.play_state.player.exp[2][0] = 0;
	game_state.play_state.player.exp[2][1] = 0;
	game_state.play_state.player.exp[2][2] = 0;
	game_state.play_state.player.x_pos     = MAP_WIDTH  / 2;
	game_state.play_state.player.y_pos     = MAP_HEIGHT / 2;
	game_state.play_state.player.sub_x_pos = 240;
	game_state.play_state.player.sub_y_pos = 240;
	
	game_state.options_menu_state.volume   = 5;
	game_state.options_menu_state.scale    = window_p->ww_scale;
	
	game_state.play_state.battle.battle_state_activity  = 0;
	game_state.play_state.battle.player_battler.sprite  = NULL;
	game_state.play_state.battle.player_battler.level   = 0;
	game_state.play_state.battle.player_battler.max_hp  = 0;
	game_state.play_state.battle.player_battler.hp      = 0;
	game_state.play_state.battle.player_battler.speed   = 0;
	game_state.play_state.battle.player_battler.baseatk = 0;
	game_state.play_state.battle.player_battler.basedef = 0;
	game_state.play_state.battle.player_battler.atk     = NULL;
	game_state.play_state.battle.player_battler.def     = NULL;
	game_state.play_state.battle.enemy_battler.sprite  = NULL;
	game_state.play_state.battle.enemy_battler.level   = 0;
	game_state.play_state.battle.enemy_battler.max_hp  = 0;
	game_state.play_state.battle.enemy_battler.hp      = 0;
	game_state.play_state.battle.enemy_battler.speed   = 0;
	game_state.play_state.battle.enemy_battler.baseatk = 0;
	game_state.play_state.battle.enemy_battler.basedef = 0;
	game_state.play_state.battle.enemy_battler.atk     = NULL;
	game_state.play_state.battle.enemy_battler.def     = NULL;
	
	// magic number for event density 1/36 units
	for(int i = 0; i < 18; i++){
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
			ww_scale_sprite(xp_sprites[i][j]);
			xp_sprites[i][j]->pad_x = (1024 / 2) - xp_sprites[i][j]->width  / 2 + (offset[i] * 128);
			xp_sprites[i][j]->pad_y = (576 / 2)  - xp_sprites[i][j]->height / 2 + (offset[j] * 128);
		}
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
