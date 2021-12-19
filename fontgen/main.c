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
	
	//~ typedef struct {
		//~ int count;
		//~ short ** arrays;
	//~ } ww_font_char_t;
	
	init_font_table();
	
	printf("{\n");
	
	for(int i = 0; i < 256; i++){
		
		if (font_lookup[i] == -1 ){
			printf("\t{ 0 },\t// %02x\n", i);
			continue;
		}
		
		char some[2];
		printf("\t{\t// %c\n", i);
		sprintf(some, "%c", i);
		ww_sprite_t * asprite = sprite_from_string(some);
		printf("\n\t},\n");
	}
	
	//~ for(int i = '0'; i < '9' +  1; i++){
		//~ char some[2];
		//~ printf("\t{\t\\\\ %c\n", i);
		//~ sprintf(some, "%c", i);
		//~ ww_sprite_t * asprite = sprite_from_string(some);
		//~ printf("\n\t},\n");
	//~ }
	
		//~ printf("\t{\t\\\\ %c\n", '.');
	//~ ww_sprite_t * a = sprite_from_string(".");
		//~ printf("\n\t},\n");
		//~ printf("\t{\t\\\\ %c\n", '!');
	//~ ww_sprite_t * b = sprite_from_string("!");
		//~ printf("\n\t},\n");
	
	printf("};");
	
	//~ ww_sprite_t * b = sprite_from_string("A");
	//~ free(b);
	
    return 0;
}
