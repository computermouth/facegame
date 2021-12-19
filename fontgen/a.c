



#include "a.h"

#define A_ANIMATION_COUNT 1
 
#define   A_ANIMATION_0_FRAME_COUNT 1
          static int A_ANIMATION_0_DELAY[] = { 2 };
	 
#define     A_ANIMATION_0_FRAME_0_POLYGON_COUNT 6
		
            
#define     A_ANIMATION_0_FRAME_0_L1_SINGLE_VERTEX_COUNT 4
			static ww_rgba_t A_ANIMATION_0_FRAME_0_L1_SINGLE_COLOR = { 255, 128, 0  };
			static short A_ANIMATION_0_FRAME_0_L1_SINGLE_X[4] = { 0, 4, 4, 0 };
			static short A_ANIMATION_0_FRAME_0_L1_SINGLE_Y[4] = { 0, 0, 1, 1 };
            
		
            
#define     A_ANIMATION_0_FRAME_0_L2_LEFT_VERTEX_COUNT 4
			static ww_rgba_t A_ANIMATION_0_FRAME_0_L2_LEFT_COLOR = { 255, 128, 0  };
			static short A_ANIMATION_0_FRAME_0_L2_LEFT_X[4] = { 0, 1, 1, 0 };
			static short A_ANIMATION_0_FRAME_0_L2_LEFT_Y[4] = { 1, 1, 2, 2 };
            
		
            
#define     A_ANIMATION_0_FRAME_0_L2_RIGHT_VERTEX_COUNT 4
			static ww_rgba_t A_ANIMATION_0_FRAME_0_L2_RIGHT_COLOR = { 255, 128, 0  };
			static short A_ANIMATION_0_FRAME_0_L2_RIGHT_X[4] = { 3, 4, 4, 3 };
			static short A_ANIMATION_0_FRAME_0_L2_RIGHT_Y[4] = { 1, 1, 2, 2 };
            
		
            
#define     A_ANIMATION_0_FRAME_0_L3_SINGLE_VERTEX_COUNT 4
			static ww_rgba_t A_ANIMATION_0_FRAME_0_L3_SINGLE_COLOR = { 255, 128, 0  };
			static short A_ANIMATION_0_FRAME_0_L3_SINGLE_X[4] = { 0, 4, 4, 0 };
			static short A_ANIMATION_0_FRAME_0_L3_SINGLE_Y[4] = { 2, 2, 3, 3 };
            
		
            
#define     A_ANIMATION_0_FRAME_0_L4_LEFT_VERTEX_COUNT 4
			static ww_rgba_t A_ANIMATION_0_FRAME_0_L4_LEFT_COLOR = { 255, 128, 0  };
			static short A_ANIMATION_0_FRAME_0_L4_LEFT_X[4] = { 0, 1, 1, 0 };
			static short A_ANIMATION_0_FRAME_0_L4_LEFT_Y[4] = { 3, 3, 4, 4 };
            
		
            
#define     A_ANIMATION_0_FRAME_0_L4_RIGHT_VERTEX_COUNT 4
			static ww_rgba_t A_ANIMATION_0_FRAME_0_L4_RIGHT_COLOR = { 255, 128, 0  };
			static short A_ANIMATION_0_FRAME_0_L4_RIGHT_X[4] = { 3, 4, 4, 3 };
			static short A_ANIMATION_0_FRAME_0_L4_RIGHT_Y[4] = { 3, 3, 4, 4 };
            
		
	


static int A_ALLOC[] = {
	/* anim */
	A_ANIMATION_COUNT,
	
	/* fram */ 
	0
	 
    + A_ANIMATION_0_FRAME_COUNT
    ,
	
	/* layr */
	0
	   
	+ A_ANIMATION_0_FRAME_0_POLYGON_COUNT
	 ,
	
	/* vert */
	0
	     
	+ A_ANIMATION_0_FRAME_0_L1_SINGLE_VERTEX_COUNT
	  
	+ A_ANIMATION_0_FRAME_0_L2_LEFT_VERTEX_COUNT
	  
	+ A_ANIMATION_0_FRAME_0_L2_RIGHT_VERTEX_COUNT
	  
	+ A_ANIMATION_0_FRAME_0_L3_SINGLE_VERTEX_COUNT
	  
	+ A_ANIMATION_0_FRAME_0_L4_LEFT_VERTEX_COUNT
	  
	+ A_ANIMATION_0_FRAME_0_L4_RIGHT_VERTEX_COUNT
	   ,
};

static int A_FRAMES[] = {
	 
    A_ANIMATION_0_FRAME_COUNT,
    
};

static int * A_DELAYS[] = {
	 
    A_ANIMATION_0_DELAY,
    
};

static int A_POLYGONS[] = {
	   
	A_ANIMATION_0_FRAME_0_POLYGON_COUNT,
	 
};

static unsigned char * A_COLORS[] = {
	     
	A_ANIMATION_0_FRAME_0_L1_SINGLE_COLOR,
	  
	A_ANIMATION_0_FRAME_0_L2_LEFT_COLOR,
	  
	A_ANIMATION_0_FRAME_0_L2_RIGHT_COLOR,
	  
	A_ANIMATION_0_FRAME_0_L3_SINGLE_COLOR,
	  
	A_ANIMATION_0_FRAME_0_L4_LEFT_COLOR,
	  
	A_ANIMATION_0_FRAME_0_L4_RIGHT_COLOR,
	   
};

static int A_VERTICES[] = {
	     
	A_ANIMATION_0_FRAME_0_L1_SINGLE_VERTEX_COUNT,
	  
	A_ANIMATION_0_FRAME_0_L2_LEFT_VERTEX_COUNT,
	  
	A_ANIMATION_0_FRAME_0_L2_RIGHT_VERTEX_COUNT,
	  
	A_ANIMATION_0_FRAME_0_L3_SINGLE_VERTEX_COUNT,
	  
	A_ANIMATION_0_FRAME_0_L4_LEFT_VERTEX_COUNT,
	  
	A_ANIMATION_0_FRAME_0_L4_RIGHT_VERTEX_COUNT,
	   
};

//~ static short * A_ARRAYS[] = {
	     
	//~ A_ANIMATION_0_FRAME_0_L1_SINGLE_X,
	//~ A_ANIMATION_0_FRAME_0_L1_SINGLE_Y,
	  
	//~ A_ANIMATION_0_FRAME_0_L2_LEFT_X,
	//~ A_ANIMATION_0_FRAME_0_L2_LEFT_Y,
	  
	//~ A_ANIMATION_0_FRAME_0_L2_RIGHT_X,
	//~ A_ANIMATION_0_FRAME_0_L2_RIGHT_Y,
	  
	//~ A_ANIMATION_0_FRAME_0_L3_SINGLE_X,
	//~ A_ANIMATION_0_FRAME_0_L3_SINGLE_Y,
	  
	//~ A_ANIMATION_0_FRAME_0_L4_LEFT_X,
	//~ A_ANIMATION_0_FRAME_0_L4_LEFT_Y,
	  
	//~ A_ANIMATION_0_FRAME_0_L4_RIGHT_X,
	//~ A_ANIMATION_0_FRAME_0_L4_RIGHT_Y,
	   
//~ };

typedef struct {
	int      count;
	short ** array;
} fontchar_t;

static fontchar_t fc_A = {
	.count = 6,
	.array = (short*[]){
		(short[]){ 0, 4, 4, 0 },
		(short[]){ 0, 0, 1, 1 },

		(short[]){ 0, 1, 1, 0 },
		(short[]){ 1, 1, 2, 2 },

		(short[]){ 3, 4, 4, 3 },
		(short[]){ 1, 1, 2, 2 },

		(short[]){ 0, 4, 4, 0 },
		(short[]){ 2, 2, 3, 3 },

		(short[]){ 0, 1, 1, 0 },
		(short[]){ 3, 3, 4, 4 },

		(short[]){ 3, 4, 4, 3 },
		(short[]){ 3, 3, 4, 4 }
	}
};

static short * A_ARRAYS[] = {
	     
	(short[]){ 0, 4, 4, 0 },
	(short[]){ 0, 0, 1, 1 },

	(short[]){ 0, 1, 1, 0 },
	(short[]){ 1, 1, 2, 2 },

	(short[]){ 3, 4, 4, 3 },
	(short[]){ 1, 1, 2, 2 },

	(short[]){ 0, 4, 4, 0 },
	(short[]){ 2, 2, 3, 3 },

	(short[]){ 0, 1, 1, 0 },
	(short[]){ 3, 3, 4, 4 },

	(short[]){ 3, 4, 4, 3 },
	(short[]){ 3, 3, 4, 4 },
	   
};

ww_reference_t A = {
	.alloc    = A_ALLOC,
	.frames   = A_FRAMES,
	.delays   = A_DELAYS,
	.polygons = A_POLYGONS,
	.colors   = A_COLORS,
	.vertices = A_VERTICES,
	.arrays   = A_ARRAYS
};

