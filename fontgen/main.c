#include <stdio.h>
#include <stdlib.h>

#include "font.h"
#include "ww.h"

int main(const int argc, const char **argv)
{
	
	//~ static short * ok[4] = {
		//~ { 0, 4, 4, 0 },
		//~ { 0, 0, 1, 1 }
	//~ };
	
	//~ return 0;
	
	//~ printf("%x\n", ok);
	
	init_font_table();
	
	for(int i = 'A'; i < 'Z' +  1; i++){
		char some[10];
		sprintf(some, "%c", i);
		ww_sprite_t * asprite = sprite_from_string(some);
	}
	
	for(int i = '0'; i < '9' +  1; i++){
		char some[10];
		sprintf(some, "%c", i);
		ww_sprite_t * asprite = sprite_from_string(some);
	}
	
	ww_sprite_t * a = sprite_from_string(".");
	ww_sprite_t * b = sprite_from_string("!");
	//~ ww_sprite_t * b = sprite_from_string("A");
	//~ free(b);
	
    return 0;
}
