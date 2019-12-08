

#ifndef _STATES_H_
#define _STATES_H_

#include <stdint.h>

typedef struct {
	uint32_t volume;
	uint32_t scale;
	enum { OPTIONS_MENU_SELECTED_VOLUME, OPTIONS_MENU_SELECTED_SCALE, OPTIONS_MENU_SELECTED_HOME } options_menu_selected;
} options_menu_state_t;

typedef struct {
	uint32_t level;
	uint32_t max_hp;
	uint32_t hp;
	uint32_t speed;
	uint32_t baseatk;
	uint32_t basedef;
	uint32_t atk[4];
	uint32_t def[4];
	uint32_t exp[9];
	int32_t x_pos;
	int32_t y_pos;
	int32_t sub_x_pos;
	int32_t sub_y_pos;
} player_t;

#define MAP_WIDTH 28
#define MAP_HEIGHT 26

typedef struct {
	uint32_t map[MAP_WIDTH][MAP_HEIGHT];
	player_t player;
	enum { PLAY_STATE_ROAM, PLAY_STATE_MENU, PLAY_STATE_DISTRACTION, PLAY_STATE_EVENT, PLAY_STATE_BATTLE, PLAY_STATE_LEVELUP, PLAY_STATE_WEAPONUP, PLAY_STATE_DEFUP } play_state_activity;
} play_state_t;

typedef struct {
	enum { TOP_STATE_IDLE, TOP_STATE_PLAY, TOP_STATE_OPTIONS, TOP_STATE_QUIT } top_state;
	enum { TOP_MENU_SELECTED_PLAY, TOP_MENU_SELECTED_OPTIONS, TOP_MENU_SELECTED_QUIT } top_menu_selected;
	play_state_t play_state;
	options_menu_state_t options_menu_state;
} game_state_t;

#endif 
