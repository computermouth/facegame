
#include "ww.h"
#include "ww_font.h"

#define CHAR_PIXEL_WIDTH 4

ww_sprite_t * ww_new_sprite_from_string(char * input, ww_rgba_t color){
	
	ww_reference_t ref = { 0 };
	
	ref.alloc = (int[]){
		1, // num_anim
		1, // num_fram
		0, // num_layr
		0, // num_vert
	};
	
	ref.frames = (int[]) { 1 }; // array of the counts of the frames per animation
	
	ref.delays = (int*[]){
		(int[]){0} // animation
		      // frame
	};
	
	ref.polygons    = (int[]) { 0 }; // array of numbers of layers per frame
	ref.colors      = NULL; // array of colors
	ref.vertices    = NULL;
	ref.arrays      = NULL;
	
	size_t len = strlen(input);
	
	for(int i = 0; i < len; i++){
		
		unsigned char ic = input[i];
		
		ww_font_char_t fc = font_chars[ic];
		if (fc.count == 0){
			//~ printf("char ['%c' -- %02x]\n", ic, ic);
			continue;
		}
		
		//~ printf("char: %c\n", ic);
		
		// totals
		ref.alloc[2] += fc.count;
		ref.alloc[3] += fc.count * CHAR_PIXEL_WIDTH;
		
		ref.polygons[0]             += fc.count;
		//~ printf("ref.polygons[0]: %d\n", ref.polygons[0]);
		
		ref.colors                   = realloc(ref.colors, sizeof(ww_rgba_t*) * ref.polygons[0]);
		for(int i = (ref.polygons[0] - fc.count); i < ref.polygons[0]; i++){
			ref.colors[i] = color;
		}
		
		ref.vertices                 = realloc(ref.vertices, sizeof(int) * ref.polygons[0]);
		for(int i = (ref.polygons[0] - fc.count); i < ref.polygons[0]; i++){
			ref.vertices[i] = CHAR_PIXEL_WIDTH;
		}
		
		ref.arrays                   = realloc(ref.arrays, sizeof(short*) * ref.polygons[0] * 2);
		
		int b = 0;
		for(int j = (ref.polygons[0] - fc.count) * 2; j < ref.polygons[0] * 2; j++){
			//~ printf("j: %d\n", j);
			//~ printf("b: %d\n", b);
			//~ printf("fc.arrays[0][0]: %d\n", fc.arrays[0][0]);
			//~ printf("src: %p\n", fc.arrays[b]);
			//~ printf("des: %p\n", ref.arrays);
			ref.arrays[j] = malloc(sizeof(short) * fc.count);
			//~ printf("des[j]: %p\n", ref.arrays[j]);
			memcpy(ref.arrays[j], fc.arrays[b], sizeof(short) * CHAR_PIXEL_WIDTH);
			for(int k = 0; k < CHAR_PIXEL_WIDTH && j % 2 == 0; k++){
				ref.arrays[j][k] += (CHAR_PIXEL_WIDTH + 2) * i;
			}
			b++;
			//~ printf("ref.arrays[j][0]: %d\n", ref.arrays[j][0]);
		}
	}
	
	ww_sprite_t * spr = ww_new_sprite(ref);
	
	free(ref.colors);
	free(ref.vertices);
	
	for(int i = 0; i < ref.polygons[0] * 2; i++)
		free(ref.arrays[i]);
	free(ref.arrays);
	
	return spr;
	
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
	//~ for(int i = 0; i < 1; i++)
		//~ printf("ref.vertices[%d]: %02d -- A.vertices[%d]: %02d\n", i, ref.vertices[i], i, A.vertices[i]);
	
	//~ printf("\n");
	//~ for(int i = 0; i < ref.alloc[2]; i++)
		//~ for(int j = 0; j < 3; j++)
			//~ printf("ref.colors[%d][%d]: %03d\n", i, j, ref.colors[i][j]);
	
	//~ printf("\n");
	//~ for(int i = 0; i < ref.alloc[2] * 2; i++)
		//~ for(int j = 0; j < CHAR_PIXEL_WIDTH; j++)
			//~ printf("ref.arrays[%d][%d]: %03d\n", i, j, ref.arrays[i][j]);
	
	//~ printf("\nsizeof(ref.alloc)/sizeof(ref.alloc[0]): %03d -- sizeof(A.alloc)/sizeof(A.alloc[0]): %03d\n",
		//~ sizeof(ref.alloc)/sizeof(ref.alloc[0]), sizeof(A.alloc)/sizeof(A.alloc[0]));
	
	//~ printf("\nsizeof(ref.frames)/sizeof(ref.frames[0]): %03d -- sizeof(A.frames)/sizeof(A.frames[0]): %03d\n",
		//~ sizeof(ref.frames)/sizeof(ref.frames[0]), sizeof(A.frames)/sizeof(A.frames[0]));
	
	//~ printf("\nsizeof(ref.polygons)/sizeof(ref.polygons[0]): %03d -- sizeof(A.polygons)/sizeof(A.polygons[0]): %03d\n",
		//~ sizeof(ref.polygons)/sizeof(ref.polygons[0]), sizeof(A.polygons)/sizeof(A.polygons[0]));
	
	//~ printf("\nsizeof(ref.vertices)/sizeof(ref.vertices[0]): %03d -- sizeof(A.vertices)/sizeof(A.vertices[0]): %03d\n",
		//~ sizeof(ref.vertices)/sizeof(ref.vertices[0]), sizeof(A.vertices)/sizeof(A.vertices[0]));
	
	//~ printf("\nsizeof(ref.delays)/sizeof(ref.delays[0]): %03d -- sizeof(A.delays)/sizeof(A.delays[0]): %03d\n",
		//~ sizeof(ref.delays)/sizeof(ref.delays[0]), sizeof(A.vertices)/sizeof(A.delays[0]));
	
	//~ printf("\nsizeof(ref.delays[0])/sizeof(ref.delays[0][0]): %03d -- sizeof(A.delays[0])/sizeof(A.delays[0][0]): %03d\n",
		//~ sizeof(ref.delays[0])/sizeof(ref.delays[0][0]), sizeof(A.delays[0])/sizeof(A.delays[0][0]));
	
	//~ printf("\nsizeof(ref.colors)/sizeof(ref.colors[0]): %03d -- sizeof(A.colors)/sizeof(A.colors[0]): %03d\n",
		//~ sizeof(ref.colors)/sizeof(ref.colors[0]), sizeof(A.vertices)/sizeof(A.colors[0]));
	
	//~ printf("\nsizeof(ref.colors[0])/sizeof(ref.colors[0][0]): %03d -- sizeof(A.colors[0])/sizeof(A.colors[0][0]): %03d\n",
		//~ sizeof(ref.colors[0])/sizeof(ref.colors[0][0]), sizeof(A.colors[0])/sizeof(A.colors[0][0]));
	
	//~ printf("\nsizeof(ref.arrays)/sizeof(ref.arrays[0]): %03d -- sizeof(A.arrays)/sizeof(A.arrays[0]): %03d\n",
		//~ sizeof(ref.arrays)/sizeof(ref.arrays[0]), sizeof(A.vertices)/sizeof(A.arrays[0]));
	
	//~ printf("\nsizeof(ref.arrays[0])/sizeof(ref.arrays[0][0]): %03d -- sizeof(A.arrays[0])/sizeof(A.arrays[0][0]): %03d\n",
		//~ sizeof(ref.arrays[0])/sizeof(ref.arrays[0][0]), sizeof(A.arrays[0])/sizeof(A.arrays[0][0]));
		
	//~ printf("REFREFREFREFREFREFREFREFREFREFREFREFREFREF\n");
	
}
