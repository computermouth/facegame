
#ifndef _FONT_H_
#define _FONT_H_

#include "ww.h"

#define NUM_LETTERS 26
#define NUM_NUMBERS 10
#define NUM_SYMBOLS 2

#define CHAR_PIXEL_WIDTH 4

typedef struct {
	int lines;
	short ** arrays;
} font_char_t;

void init_font_table();
font_char_t get_font_char(unsigned char input, int index);
ww_sprite_t * sprite_from_string(char * input);

#endif
