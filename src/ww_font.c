
#include "ww.h"
#include "ww_font.h"

#include "a.h"

#define CHAR_PIXEL_WIDTH 4

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

ww_sprite_t * ww_new_sprite_from_string(char * input, ww_rgba_t color){
	
	ww_reference_t * ref = NULL;
	ref = malloc(sizeof(ww_reference_t));
	
	ref->alloc = malloc(sizeof(int) * 4);
	ref->alloc[0] = 1; // num_anim
	ref->alloc[1] = 1; // num_fram
	ref->alloc[2] = 0; // num_layr
	ref->alloc[3] = 0; // num_vert
	
	ref->frames = malloc(sizeof(int) * ref->alloc[1]);
	ref->frames[0] = 1; // array of the counts of the frames per animation
	
	ref->delays    = malloc(sizeof(int*) * ref->alloc[1]);
	ref->delays[0] = malloc(sizeof(int)  * ref->alloc[1]);
	ref->delays[0][0] = 0; // array of pointers to array of delays between frames
	        //[a][f]
	
	ref->polygons    = malloc(sizeof(int) * 1); // array of numbers of layers per frame
	ref->polygons[0] = 0;
	ref->colors      = NULL; // array of colors
	ref->vertices    = NULL;
	ref->arrays      = NULL;
	
	size_t len = strlen(input);
	
	for(int i = 0; i < len; i++){
		
		unsigned char ic = input[i];
		if (ic == ' ')
			continue;
		
		ww_font_char_t fc = font_chars[ic];
		if (fc.count == 0){
			printf("char  not found\n");
			continue;
		}
		
		printf("font_chars['!'].count:        %d\n", font_chars['!'].count);
		printf("font_chars['!'].arrays[0][0]: %d\n", font_chars['!'].arrays[0][0]);
		printf("char: %c\n", ic);
		
		// totals
		ref->alloc[2] += fc.count;
		ref->alloc[3] += fc.count * CHAR_PIXEL_WIDTH;
		
		ref->polygons[0]             += fc.count;
		printf("ref->polygons[0]: %d\n", ref->polygons[0]);
		
		ref->colors                   = realloc(ref->colors, sizeof(ww_rgba_t*) * ref->polygons[0]);
		for(int i = (ref->polygons[0] - fc.count); i < ref->polygons[0]; i++){
			ref->colors[i] = color;
		}
		
		ref->vertices                 = realloc(ref->vertices, sizeof(int) * ref->polygons[0]);
		for(int i = (ref->polygons[0] - fc.count); i < ref->polygons[0]; i++){
			ref->vertices[i] = CHAR_PIXEL_WIDTH;
		}
		
		ref->arrays                   = realloc(ref->arrays, sizeof(short*) * ref->polygons[0] * 2);
		
		int b = 0;
		for(int i = (ref->polygons[0] - fc.count) * 2; i < ref->polygons[0] * 2; i++){
			printf("i: %d\n", i);
			printf("b: %d\n", b);
			printf("fc.arrays[0][0]: %d\n", fc.arrays[0][0]);
			printf("src: %p\n", fc.arrays[b]);
			printf("des: %p\n", ref->arrays);
			//~ printf("ref->polygons[0] + i: %d\n", ref->polygons[0] + i);
			ref->arrays[i] = malloc(sizeof(short) * fc.count);
			printf("des[i]: %p\n", ref->arrays[i]);
			memcpy(ref->arrays[i], fc.arrays[b], sizeof(short) * CHAR_PIXEL_WIDTH);
			b++;
			printf("ref->arrays[i][0]: %d\n", ref->arrays[i][0]);
		}
	}
	
	
	
	for(int i = 0; i < 4; i++)
		printf("ref.alloc[%d]: %02d -- A.alloc[%d]: %02d\n", i, ref->alloc[i], i, A.alloc[i]);
	
	printf("\n");
	for(int i = 0; i < 1; i++)
		printf("ref.frames[%d]: %02d -- A.frames[%d]: %02d\n", i, ref->frames[i], i, A.frames[i]);
	
	printf("\n");
	for(int i = 0; i < 1; i++)
		printf("ref.delays[%d][0]: %02d -- A.delays[%d][0]: %02d\n", i, ref->delays[i][0], i, A.delays[i][0]);
	
	printf("\n");
	for(int i = 0; i < 1; i++)
		printf("ref.polygons[%d]: %02d -- A.polygons[%d]: %02d\n", i, ref->polygons[i], i, A.polygons[i]);
	
	printf("\n");
	for(int i = 0; i < 1; i++)
		printf("ref.vertices[%d]: %02d -- A.vertices[%d]: %02d\n", i, ref->vertices[i], i, A.vertices[i]);
	
	printf("\n");
	for(int i = 0; i < ref->alloc[2]; i++)
		for(int j = 0; j < 3; j++)
			printf("ref.colors[%d][%d]: %03d -- A.colors[%d][%d]: %03d\n", i, j, ref->colors[i][j], i, j, A.colors[i][j]);
	
	printf("\n");
	for(int i = 0; i < ref->alloc[2] * 2; i++)
		for(int j = 0; j < CHAR_PIXEL_WIDTH; j++)
			printf("ref.arrays[%d][%d]: %03d -- A.arrays[%d][%d]: %03d\n", i, j, ref->arrays[i][j], i, j, A.arrays[i][j]);
	
	printf("\nsizeof(ref.alloc)/sizeof(ref.alloc[0]): %03d -- sizeof(A.alloc)/sizeof(A.alloc[0]): %03d\n",
		sizeof(ref->alloc)/sizeof(ref->alloc[0]), sizeof(A.alloc)/sizeof(A.alloc[0]));
	
	printf("\nsizeof(ref.frames)/sizeof(ref.frames[0]): %03d -- sizeof(A.frames)/sizeof(A.frames[0]): %03d\n",
		sizeof(ref->frames)/sizeof(ref->frames[0]), sizeof(A.frames)/sizeof(A.frames[0]));
	
	printf("\nsizeof(ref.polygons)/sizeof(ref.polygons[0]): %03d -- sizeof(A.polygons)/sizeof(A.polygons[0]): %03d\n",
		sizeof(ref->polygons)/sizeof(ref->polygons[0]), sizeof(A.polygons)/sizeof(A.polygons[0]));
	
	printf("\nsizeof(ref.vertices)/sizeof(ref.vertices[0]): %03d -- sizeof(A.vertices)/sizeof(A.vertices[0]): %03d\n",
		sizeof(ref->vertices)/sizeof(ref->vertices[0]), sizeof(A.vertices)/sizeof(A.vertices[0]));
	
	printf("\nsizeof(ref.delays)/sizeof(ref.delays[0]): %03d -- sizeof(A.delays)/sizeof(A.delays[0]): %03d\n",
		sizeof(ref->delays)/sizeof(ref->delays[0]), sizeof(A.vertices)/sizeof(A.delays[0]));
	
	printf("\nsizeof(ref.delays[0])/sizeof(ref.delays[0][0]): %03d -- sizeof(A.delays[0])/sizeof(A.delays[0][0]): %03d\n",
		sizeof(ref->delays[0])/sizeof(ref->delays[0][0]), sizeof(A.delays[0])/sizeof(A.delays[0][0]));
	
	printf("\nsizeof(ref.colors)/sizeof(ref.colors[0]): %03d -- sizeof(A.colors)/sizeof(A.colors[0]): %03d\n",
		sizeof(ref->colors)/sizeof(ref->colors[0]), sizeof(A.vertices)/sizeof(A.colors[0]));
	
	printf("\nsizeof(ref.colors[0])/sizeof(ref.colors[0][0]): %03d -- sizeof(A.colors[0])/sizeof(A.colors[0][0]): %03d\n",
		sizeof(ref->colors[0])/sizeof(ref->colors[0][0]), sizeof(A.colors[0])/sizeof(A.colors[0][0]));
	
	printf("\nsizeof(ref.arrays)/sizeof(ref.arrays[0]): %03d -- sizeof(A.arrays)/sizeof(A.arrays[0]): %03d\n",
		sizeof(ref->arrays)/sizeof(ref->arrays[0]), sizeof(A.vertices)/sizeof(A.arrays[0]));
	
	printf("\nsizeof(ref.arrays[0])/sizeof(ref.arrays[0][0]): %03d -- sizeof(A.arrays[0])/sizeof(A.arrays[0][0]): %03d\n",
		sizeof(ref->arrays[0])/sizeof(ref->arrays[0][0]), sizeof(A.arrays[0])/sizeof(A.arrays[0][0]));
	
	short ok[CHAR_PIXEL_WIDTH] = { 123, 123, 123, 123 };
	
	for(int i = 0; i < ref->polygons[0]; i++){
		printf("memcmp(ref->arrays[%d], A.arrays[%d], sizeof(char) * CHAR_PIXEL_WIDTH): %03d\n", i, i, memcmp(ref->arrays[i], A.arrays[i], sizeof(char) * sizeof(short) * CHAR_PIXEL_WIDTH));
	}
	
	//~ for(int i = 0; i < 4; i++)
		//~ printf("alloc[%d]: %d\n", i, ref->alloc[i]);
	
	//~ for(int i = 0; i < ref->alloc[0]; i++)
		//~ printf("frames[%d]: %d\n", i, ref->frames[i]);
	
	
	printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
	
	//~ ww_sprite_t * a = ww_new_sprite(A);
	printf("REFREFREFREFREFREFREFREFREFREFREFREFREFREF\n");
	
	return ww_new_sprite(*ref);
	
	printf("ENDNENDNNENEENDNNENDNNENENDNDNENENDNNDEND\n");
	
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
