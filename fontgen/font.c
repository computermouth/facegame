
#include <stdlib.h>
#include <string.h>

#include "ww.h"
#include "font.h"

#include "a.h"

const unsigned short font[(NUM_LETTERS + NUM_NUMBERS + NUM_SYMBOLS) * 2] = {
	
	// A
	(0x0F      ) | // 1111
	(0x09 << 4 ) | // 1001
	(0x0F << 8 ) | // 1111
	(0x09 << 12),  // 1001
	
	// B
	(0x0F      ) | // 1111
	(0x0E << 4 ) | // 1110
	(0x09 << 8 ) | // 1001
	(0x0F << 12),  // 1111
	
	// C
	(0x0F      ) | // 1111
	(0x08 << 4 ) | // 1000
	(0x08 << 8 ) | // 1000
	(0x0F << 12),  // 1111
	
	// D
	(0x0E      ) | // 1110
	(0x09 << 4 ) | // 1001
	(0x09 << 8 ) | // 1001
	(0x09 << 12),  // 1110
	
	// E
	(0x0F      ) | // 1111
	(0x0E << 4 ) | // 1110
	(0x08 << 8 ) | // 1000
	(0x0F << 12),  // 1111
	
	// F
	(0x0F      ) | // 1111
	(0x0E << 4 ) | // 1110
	(0x08 << 8 ) | // 1000
	(0x0F << 12),  // 1111
	
	// G
	(0x0F      ) | // 1111
	(0x08 << 4 ) | // 1000
	(0x09 << 8 ) | // 1001
	(0x0F << 12),  // 1111
	
	// H
	(0x09      ) | // 1001
	(0x09 << 4 ) | // 1001
	(0x0F << 8 ) | // 1111
	(0x09 << 12),  // 1001
	
	// I
	(0x0F      ) | // 1111
	(0x02 << 4 ) | // 0010
	(0x02 << 8 ) | // 0010
	(0x0F << 12),  // 1111
	
	// J
	(0x0F      ) | // 1111
	(0x01 << 4 ) | // 0001
	(0x09 << 8 ) | // 1001
	(0x0F << 12),  // 1111
	
	// K
	(0x09      ) | // 1001
	(0x0E << 4 ) | // 1110
	(0x09 << 8 ) | // 1001
	(0x09 << 12),  // 1001
	
	// L
	(0x08      ) | // 1000
	(0x08 << 4 ) | // 1000
	(0x08 << 8 ) | // 1000
	(0x0F << 12),  // 1111
	
	// M
	(0x0F      ) | // 1111
	(0x0B << 4 ) | // 1011
	(0x0B << 8 ) | // 1011
	(0x09 << 12),  // 1001
	
	// N
	(0x0D      ) | // 1101
	(0x0B << 4 ) | // 1011
	(0x09 << 8 ) | // 1001
	(0x09 << 12),  // 1001
	
	// O
	(0x0F      ) | // 1111
	(0x09 << 4 ) | // 1001
	(0x09 << 8 ) | // 1001
	(0x0F << 12),  // 1111
	
	// P
	(0x0F      ) | // 1111
	(0x09 << 4 ) | // 1001
	(0x0F << 8 ) | // 1111
	(0x08 << 12),  // 1000
	
	// Q
	(0x0F      ) | // 1111
	(0x09 << 4 ) | // 1001
	(0x0B << 8 ) | // 1011
	(0x0F << 12),  // 1111
	
	// R
	(0x0F      ) | // 1111
	(0x09 << 4 ) | // 1001
	(0x0F << 8 ) | // 1111
	(0x0A << 12),  // 1010
	
	// S
	(0x0F      ) | // 1111
	(0x0E << 4 ) | // 1110
	(0x01 << 8 ) | // 0001
	(0x0F << 12),  // 1111
	
	// T
	(0x0F      ) | // 1111
	(0x02 << 4 ) | // 0010
	(0x02 << 8 ) | // 0010
	(0x02 << 12),  // 0010
	
	// U
	(0x09      ) | // 1001
	(0x09 << 4 ) | // 1001
	(0x09 << 8 ) | // 1001
	(0x0F << 12),  // 1111
	
	// V
	(0x09      ) | // 1001
	(0x09 << 4 ) | // 1001
	(0x09 << 8 ) | // 1001
	(0x06 << 12),  // 0110
	
	// W
	(0x09      ) | // 1001
	(0x0B << 4 ) | // 1011
	(0x0B << 8 ) | // 1011
	(0x0F << 12),  // 1111
	
	// X
	(0x09      ) | // 1001
	(0x06 << 4 ) | // 0110
	(0x06 << 8 ) | // 0110
	(0x09 << 12),  // 1001
	
	// Y
	(0x09      ) | // 1001
	(0x09 << 4 ) | // 1001
	(0x0F << 8 ) | // 1111
	(0x02 << 12),  // 0010
	
	// Z
	(0x0F      ) | // 1111
	(0x02 << 4 ) | // 0010
	(0x04 << 8 ) | // 0100
	(0x0F << 12),  // 1111
	
	// 0
	(0x0F      ) | // 1111
	(0x09 << 4 ) | // 1001
	(0x09 << 8 ) | // 1001
	(0x0F << 12),  // 1111
	
	// 1
	(0x02      ) | // 0010
	(0x02 << 4 ) | // 0010
	(0x02 << 8 ) | // 0010
	(0x02 << 12),  // 0010
	
	// 2
	(0x0F      ) | // 1111
	(0x01 << 4 ) | // 0001
	(0x0E << 8 ) | // 1110
	(0x0F << 12),  // 1111
	
	// 3
	(0x0F      ) | // 1111
	(0x07 << 4 ) | // 0111
	(0x01 << 8 ) | // 0001
	(0x0F << 12),  // 1111
	
	// 4
	(0x09      ) | // 1001
	(0x09 << 4 ) | // 1001
	(0x0F << 8 ) | // 1111
	(0x01 << 12),  // 0001
	
	// 5
	(0x0F      ) | // 1111
	(0x08 << 4 ) | // 1000
	(0x07 << 8 ) | // 0111
	(0x0F << 12),  // 1111
	
	// 6
	(0x08      ) | // 1000
	(0x0F << 4 ) | // 1111
	(0x09 << 8 ) | // 1001
	(0x0F << 12),  // 1111
	
	// 7
	(0x0F      ) | // 1111
	(0x01 << 4 ) | // 0001
	(0x01 << 8 ) | // 0001
	(0x01 << 12),  // 0001
	
	// 8
	(0x07      ) | // 0111
	(0x0D << 4 ) | // 1101
	(0x0B << 8 ) | // 1011
	(0x0E << 12),  // 1110
	
	// 9
	(0x07      ) | // 0111
	(0x0D << 4 ) | // 1101
	(0x0B << 8 ) | // 1011
	(0x0E << 12),  // 1110
	
	// .
	(0x00      ) | // 0000
	(0x00 << 4 ) | // 0000
	(0x00 << 8 ) | // 0000
	(0x08 << 12),  // 1000
	
	// !
	(0x08      ) | // 1000
	(0x08 << 4 ) | // 1000
	(0x00 << 8 ) | // 0000
	(0x08 << 12)   // 1000
};

short font_lookup[256] = { -1 };

const short horizontals[4][2][4] = {
	// 1
	{
		{ 0, 1, 1, 0 },
		{ 0, 0, 1, 1 },
	},
	// 2
	{
		{ 0, 2, 2, 0 },
		{ 0, 0, 1, 1 },
	},
	// 3
	{
		{ 0, 3, 3, 0 },
		{ 0, 0, 1, 1 },
	},
	// 4
	{
		{ 0, 4, 4, 0 },
		{ 0, 0, 1, 1 },
	},
};

// set whole table to -1
// set the following programattically
void init_font_table(){
	
	memset(font_lookup, -1, sizeof(short) * 256);
	
	font_lookup['A'] =  0;
	font_lookup['B'] =  1;
	font_lookup['C'] =  2;
	font_lookup['D'] =  3;
	font_lookup['E'] =  4;
	font_lookup['F'] =  5;
	font_lookup['G'] =  6;
	font_lookup['H'] =  7;
	font_lookup['I'] =  8;
	font_lookup['J'] =  9;
	font_lookup['K'] = 10;
	font_lookup['L'] = 11;
	font_lookup['M'] = 12;
	font_lookup['N'] = 13;
	font_lookup['O'] = 14;
	font_lookup['P'] = 15;
	font_lookup['Q'] = 16;
	font_lookup['R'] = 17;
	font_lookup['S'] = 18;
	font_lookup['T'] = 19;
	font_lookup['U'] = 20;
	font_lookup['V'] = 21;
	font_lookup['W'] = 22;
	font_lookup['X'] = 23;
	font_lookup['Y'] = 24;
	font_lookup['Z'] = 25;
	font_lookup['0'] = 26;
	font_lookup['1'] = 27;
	font_lookup['2'] = 28;
	font_lookup['3'] = 29;
	font_lookup['4'] = 30;
	font_lookup['5'] = 31;
	font_lookup['6'] = 32;
	font_lookup['7'] = 33;
	font_lookup['8'] = 34;
	font_lookup['9'] = 35;
	font_lookup['.'] = 36;
	font_lookup['!'] = 37;
}

font_char_t get_font_char(unsigned char input, int index){
	
	font_char_t rc = { .lines = 0, .arrays = NULL };
	
	//~ printf("get_font_char -- input: %c -- index: %d\n", input, index);
	
	unsigned char font_index = font_lookup[input];
	
	//~ printf("font_index: %u\n", font_index);
	
	unsigned short output_char = font[font_index];
	
	//~ printf("output_char: %04x\n", output_char);
	
	//~ unsigned char nibs[4];
	
	for(int i = 0; i < 4; i++){
		unsigned char nib = (output_char >> i * 4) % 0x10;
		//~ printf("nib: %02x\n", nib);
		
		//~ unsigned char bits[4];
		int size = 0;
		for(int j = 0; j < 5; j++) {
			
			// start line
			if ( nib & ( 0x08 >> j) && j < 5) {
				
				if (size == 0){
					rc.lines++;
					//~ printf("bit is yes, rc.lines++\n");
				}
				size++;
			}
			
			//~ int end = 0;
			//~ if (j == 3 || !(nib & ( 0x08 >> j)))
				//~ end = 1;
			
			// end line
			if ( !(nib & ( 0x08 >> j)) && size != 0 ) {
				
				//~ if (j == 3) // HEREHEREHEREHEREHERE
					//~ j++;
					
				rc.arrays = realloc(rc.arrays, sizeof(short*) * (rc.lines * 2));
				rc.arrays[rc.lines * 2 - 2] = malloc(sizeof(short) * CHAR_PIXEL_WIDTH);
				rc.arrays[rc.lines * 2 - 1] = malloc(sizeof(short) * CHAR_PIXEL_WIDTH);
				memcpy(rc.arrays[rc.lines * 2 - 2], horizontals[size - 1][0], sizeof(short) * CHAR_PIXEL_WIDTH);
				memcpy(rc.arrays[rc.lines * 2 - 1], horizontals[size - 1][1], sizeof(short) * CHAR_PIXEL_WIDTH);
				
				//~ if (j == 3)
					//~ break;
				
				//~ printf("i: %d j: %d s %d\n", i, j, size);
				
				//~ printf("rc.arrays[%d]:", rc.lines * 2 - 2);
				for(int k = 0; k < CHAR_PIXEL_WIDTH; k++){
					// bullshit but works
					// should have null terminated, and done it by 5's
					//~ if (size != 4 && j != 1)
					//~ rc.arrays[rc.lines * 2 - 2][k] += j - size; // HEREHEREHEREHEREHERE
					//~ rc.arrays[rc.lines * 2 - 2][k] += j - size; // HEREHEREHEREHEREHERE
					
					// OR???
					//~ rc.arrays[rc.lines * 2 - 2][k] += abs(j - size);
					rc.arrays[rc.lines * 2 - 2][k] += j - size;
					
					//~ printf(" %d", rc.arrays[rc.lines * 2 - 2][k]);
				}
				//~ printf("\n");
				
				//~ printf("rc.arrays[%d]:", rc.lines * 2 - 1);
				for(int k = 0; k < CHAR_PIXEL_WIDTH; k++){
					rc.arrays[rc.lines * 2 - 1][k] += i;
					//~ printf(" %d", rc.arrays[rc.lines * 2 - 1][k]);
				}
				//~ printf("\n");
				
				j++;
				
				//~ printf("\nfinal size: %d\n", size);
				size = 0;
				
				//~ printf("rc.arrays[%ld *2 - 2][0]: %u\n", rc.lines, rc.arrays[rc.lines *2 - 2][0]);
			}
			//~ printf("loop -- lines: %d\n", rc.lines);
			//~ printf("loop -- size: %d\n", size);
		}
	}
	
	//~ for(int i = 1; i <= rc.lines; i++)
		//~ for(int j = 0; j < CHAR_PIXEL_WIDTH; j++)
			//~ rc.arrays[i * 2 - 2][j] = (rc.arrays[i * 2 - 2][j] + 1) * index;
	
	return rc;
	
}

ww_sprite_t * sprite_from_string(char * input){
	
	ww_reference_t ref = { 0 };
	size_t len = strlen(input);
	
	ref.alloc = malloc(sizeof(int) *
		(
			1   + // anim_count
			1   + // fram_count
			1   + // layr_count
			1     // vert_count
		)
	);	
	
	//~ printf("sizeof(ref.alloc): %02d -- sizeof(A.alloc): %02d\n", sizeof(ref.alloc)/sizeof(ref.alloc[0]), sizeof(A.alloc)/sizeof(A.alloc[0]));
		
	// animations
	ref.alloc[0] = 1;
	// frames
	ref.alloc[1] = 1;
	// layers
	ref.alloc[2] = 0;
	// vertices
	ref.alloc[3] = 0;
	
	ww_rgba_t color = { 255, 128, 0 };
	
	int frames[1] = {1};
	ref.frames = frames;
	
	int delays[1] = {0};
	ref.delays = malloc(sizeof(int*) * 1);
	ref.delays[0] = delays;
	
	int total_lines = 0;
	
	for(int i = 0; i < len; i++){
		font_char_t fc = get_font_char(input[i], i);
		
		// layers
		ref.alloc[2] += fc.lines;
		// vertices
		ref.alloc[3] += fc.lines * CHAR_PIXEL_WIDTH;
		
		ref.polygons = realloc(ref.polygons, sizeof(int)         * (total_lines + fc.lines)    );
		ref.colors   = realloc(ref.colors  , sizeof(ww_rgba_t *) * (total_lines + fc.lines)    );
		ref.vertices = realloc(ref.vertices, sizeof(int)         * (total_lines + fc.lines)    );
		ref.arrays   = realloc(ref.arrays  , sizeof(short*)      * (total_lines + fc.lines) * 2);
		
		ref.polygons[i] = fc.lines;
		ref.vertices[i] = CHAR_PIXEL_WIDTH;
		
		for(int j = 0; j < fc.lines; j++){
			ref.colors[total_lines + j] = color;
			
			//~ ref.arrays[total_lines + j] = malloc(sizeof(short) * CHAR_PIXEL_WIDTH);
			//~ memcpy(ref.arrays[total_lines + j], fc.arrays[j], sizeof(short) * CHAR_PIXEL_WIDTH);
			//~ free(fc.arrays[j]);
		}
		//~ printf("ok\n");
		
		for(int j = 1; j < fc.lines + 1; j++){
			ref.arrays[(total_lines + j) * 2 - 2] = malloc(sizeof(short) * CHAR_PIXEL_WIDTH);
			memcpy(ref.arrays[(total_lines + j) * 2 - 2], fc.arrays[j * 2 - 2], sizeof(short) * CHAR_PIXEL_WIDTH);
			free(fc.arrays[j * 2 - 2]);
			
			ref.arrays[(total_lines + j) * 2 - 1] = malloc(sizeof(short) * CHAR_PIXEL_WIDTH);
			memcpy(ref.arrays[(total_lines + j) * 2 - 1], fc.arrays[j * 2 - 1], sizeof(short) * CHAR_PIXEL_WIDTH);
			free(fc.arrays[j * 2 - 1]);
		}
		
		printf("\t\t.count = %d,\n", fc.lines);
		printf("\t\t.arrays = (short*[]){\n");
		for(int j = 1; j < fc.lines + 1; j++){
			printf("\t\t\t(short[]){ %d, %d, %d, %d },\n",
				ref.arrays[(total_lines + j) * 2 - 2][0],
				ref.arrays[(total_lines + j) * 2 - 2][1],
				ref.arrays[(total_lines + j) * 2 - 2][2],
				ref.arrays[(total_lines + j) * 2 - 2][3]
			);
			printf("\t\t\t(short[]){ %d, %d, %d, %d }",
				ref.arrays[(total_lines + j) * 2 - 1][0],
				ref.arrays[(total_lines + j) * 2 - 1][1],
				ref.arrays[(total_lines + j) * 2 - 1][2],
				ref.arrays[(total_lines + j) * 2 - 1][3]
			);
			if (j != fc.lines) printf(",\n\n");
		}
			printf("\n\t\t}");
		
		/*
		printf("#define      FONT_%c_POLYGON_COUNT %d\n", input[i], fc.lines);
		printf("static short FONT_%c_X[FONT_%c_POLYGON_COUNT][CHAR_PIXEL_WIDTH] = {\n\n", input[i], input[i]);
		for(int j = 1; j < fc.lines + 1; j++){
			printf("\t(short[]){ %d, %d, %d, %d },\n",
				ref.arrays[(total_lines + j) * 2 - 2][0],
				ref.arrays[(total_lines + j) * 2 - 2][1],
				ref.arrays[(total_lines + j) * 2 - 2][2],
				ref.arrays[(total_lines + j) * 2 - 2][3]
			);
			printf("\t(short[]){ %d, %d, %d, %d }",
				ref.arrays[(total_lines + j) * 2 - 1][0],
				ref.arrays[(total_lines + j) * 2 - 1][1],
				ref.arrays[(total_lines + j) * 2 - 1][2],
				ref.arrays[(total_lines + j) * 2 - 1][3]
			);
			if (j != fc.lines) printf(",\n\n");
			printf("\n");
		}
		printf("\n};\n");
		*/
		
		//~ printf("static short FONT_%c_Y[FONT_%c_POLYGON_COUNT][CHAR_PIXEL_WIDTH] = {\n", input[i], input[i]);
		//~ for(int j = 1; j < fc.lines + 1; j++){
			//~ printf("\t{ %d, %d, %d, %d }",
				//~ ref.arrays[(total_lines + j) * 2 - 1][0],
				//~ ref.arrays[(total_lines + j) * 2 - 1][1],
				//~ ref.arrays[(total_lines + j) * 2 - 1][2],
				//~ ref.arrays[(total_lines + j) * 2 - 1][3]
			//~ );
			//~ if (j != fc.lines) printf(",");
			//~ printf("\n");
		//~ }
		//~ printf("};\n\n\n");
		
		//~ printf("\n");
		//~ for(int j = 1; j < fc.lines + 1; j++){
			//~ printf("static short FONT_%c_%d_Y = {", input[i], j - 1);
			//~ for(int k = 0; k < CHAR_PIXEL_WIDTH; k++){
				//~ printf(" %d", ref.arrays[(total_lines + j) * 2 - 1][k]);
				//~ if (k != CHAR_PIXEL_WIDTH - 1) printf(",", ref.arrays[(total_lines + j) * 2 - 2][k]);
			//~ }
			//~ printf(" };\n", input[i], j - 1);
		//~ }
		//~ printf("\n\n");
		
		
		//~ printf("ok\n");
		free(fc.arrays);
		
		total_lines += fc.lines;
		
		
		//~ for(int i = 0; i < fc.lines; i++){
			//~ printf("#define    FONT_%c_POLYGON_COUNT    %d\n", input[i], fc.lines);
		//~ }
	}
	
	
	//~ for(int i = 0; i < 4; i++)
		//~ printf("ref.alloc[%d]: %02d -- A.alloc[%d]: %02d\n", i, ref.alloc[i], i, A.alloc[i]);
	
	//~ printf("\n");
	//~ for(int i = 0; i < 1; i++)
		//~ printf("ref.frames[%d]: %02d -- A.frames[%d]: %02d\n", i, ref.frames[i], i, A.frames[i]);
	
	//~ printf("\n");
	//~ for(int i = 0; i < 1; i++)
		//~ printf("ref.delays[%d][0]: %02d -- A.delays[%d][0]: %02d\n", i, ref.delays[i][0], i, A.delays[i][0]);
	
	//~ printf("\n");
	//~ for(int i = 0; i < 1; i++)
		//~ printf("ref.polygons[%d]: %02d -- A.polygons[%d]: %02d\n", i, ref.polygons[i], i, A.polygons[i]);
	
	//~ printf("\n");
	//~ for(int i = 0; i < ref.alloc[2]; i++)
		//~ for(int j = 0; j < 3; j++)
			//~ printf("ref.colors[%d][%d]: %03d -- A.colors[%d][%d]: %03d\n", i, j, ref.colors[i][j], i, j, A.colors[i][j]);
	
	//~ printf("\n");
	//~ for(int i = 0; i < ref.alloc[2] * 2; i++)
		//~ for(int j = 0; j < CHAR_PIXEL_WIDTH; j++)
			//~ printf("ref.arrays[%d][%d]: %03d -- A.arrays[%d][%d]: %03d\n", i, j, ref.arrays[i][j], i, j, A.arrays[i][j]);
	
	
	//~ ww_sprite_t * spr = ww_new_sprite(ref);
	
	free(ref.alloc   );
	free(ref.delays  );
	free(ref.polygons);
	free(ref.colors  );
	free(ref.vertices);
	
	for(int j = 0; j < total_lines * 2; j++){
		free(ref.arrays[j]);
	}
	free(ref.arrays  );
	
	
	
	return NULL;
}

/*

typedef struct {
	int * alloc;
	int * frames;
	int ** delays;
	int * polygons;
	unsigned char ** colors;
	int * vertices;
	short ** arrays;
} ww_reference_t;

*/







































