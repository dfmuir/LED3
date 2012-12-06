
#include "buffer.c"




////////////////////////   SHIFT EFFECTS   ////////////////////////////


//void shift_front_to_back {
//    return;
//}



////////////////////////   STILL FRAMES   ////////////////////////////

/* Shapes */

//x,y z denote bottom left corner

void create_cube_outline(int bl_x, int bl_y, int bl_z, int tr_x, int tr_y, int tr_z, colorType color) {
    int lx, ly, lz;

    for(lx = bl_x; lx <= tr_x; lx++) {
        set_single_led_color(lx, tr_y, tr_z, color);
        set_single_led_color(lx, bl_y, tr_z, color);
        set_single_led_color(lx, tr_y, bl_z, color);
        set_single_led_color(lx, bl_y, bl_z, color);
    }
    
    for(ly = bl_y; ly <= tr_y; ly++) {
        set_single_led_color(tr_x, ly, tr_z, color);
        set_single_led_color(bl_x, ly, tr_z, color);
        set_single_led_color(tr_x, ly, bl_z, color);
        set_single_led_color(bl_x, ly, bl_z, color);
    }
    
    for(lz = bl_z; lz <= tr_z; lz++) {
        set_single_led_color(tr_x, tr_y, lz, color);
        set_single_led_color(bl_x, tr_y, lz, color);
        set_single_led_color(tr_x, bl_y, lz, color);
        set_single_led_color(bl_x, bl_y, lz, color);
    }
}

void create_cube(int x, int y, int z, int size, colorType outer_color, colorType inner_color) {
    int lx, ly, lz;
    for(lz = z; lz < size+z; lz++) {
        for(ly = y; ly < size+y; ly++) {
            for(lx = x; lx < size+x; lx++) {
                if((lx == x || lx == size+x-1) + (ly == y || ly == size+y-1) + (lz == z || lz == size+z-1) > 1) {
                    set_single_led_color(lx,ly,lz, outer_color);
                }
                else {
                    set_single_led_color(lx,ly,lz, inner_color);
                }
            }
        }
    }
}


void create_cube_walls(int x, int y, int z, int size, colorType outer_color, colorType inner_color) {
    int lx, ly, lz;
    for(lz = z; lz < size+z; lz++) {
        for(ly = y; ly < size+y; ly++) {
            for(lx = x; lx < size+x; lx++) {
                if(lx == x || lx == size+x-1 || ly == y || ly == size+y-1 || lz == z || lz == size+z-1) {
                    set_single_led_color(lx,ly,lz, outer_color);
                }
                else {
                    set_single_led_color(lx,ly,lz, inner_color);
                }
            }
        }
    }
}


/* Letters */
void letter_L(int row, colorType color){
    int i;
    for( i = 0; i < 8; i++ ){
        int j;
        if( i < 2 ){
            for(j = 1; j < 7; j++ )
                set_single_led_color( j, i, row, color );
        }
        else {
            for(j = 1; j < 3; j++ )
                set_single_led_color( j, i, row, color );
        }
    }
}


void letter_E(int row, colorType color){
    int i;
    for( i = 0; i < 8; i++ ){
        int j;
        if( i < 2 || i > 5){
            for(j = 1; j < 7; j++ )
                set_single_led_color( j, i, row, color );
        }
        else if( i == 3 || i == 4 ){
            for(j = 1; j < 5; j++)
                set_single_led_color( j, i, row, color );
        }
        else{
            for( j = 1; j < 3; j++ )
                set_single_led_color( j, i, row, color );
        }
    }
}

void letter_D(int row, colorType color){
    int i, j;
    for( i = 0; i < 8; i++ ){
        if( i == 1 || i == 6){
            for( j = 1; j < 6; j++ )
                set_single_led_color( j, i, row, color );
        }
        else if( i == 0 || i == 7){
            for( j = 1; j < 5; j++)
                set_single_led_color( j, i, row, color );
        }
        else{
            for( j = 1; j < 3; j++ )
                set_single_led_color( j, i, row, color );
            for( j = 5; j < 7; j++ )
                set_single_led_color( j, i, row, color );
        }
    }
}

void letter_3(int row, colorType color){
    int i;
    int j;
    for( i = 0; i < 8; i++ ){
        if( i == 1 || i == 6){
            for(j = 1; j < 7; j++ )
                set_single_led_color( j, i, row, color );
        }
        else if( i == 0 || i == 7) {
            for(j = 1; j < 6; j++ )
                set_single_led_color( j, i, row, color );
        }
        else if( i == 3 || i == 4 ){
            for(j = 3; j < 7; j++)
                set_single_led_color( j, i, row, color );
        }
        else{
            for( j = 5; j < 7; j++ )
                set_single_led_color( j, i, row, color );
        }
    }
    
}

void rainMaker_frame(int maxNumOfDrops, colorType color){
	// Assuming all new LED's will turn on in layer 7
	int xCord, zCord;
	int max = maxNumOfDrops;

	if( maxNumOfDrops >= 64 ) max = 64 ;
	int rain = rand()%(max);		// Number of raindrops

	int i;
	for( i = 0; i < rain; i++ ){				// rain = iterations
		xCord = rand()%8;			// x-axis random coordinate 
		zCord = rand()%8;			// y-axis random coordinate
        set_single_led_color( xCord, 7, zCord, color );		// turn-on LED in layer 7
    }						// end of for loop
}

void danceAlienUp_frame( colorType color ){
	int i, j, z, move_count;	
	z = 0;
	
		// Frame 1
		for( i = 0; i < 8; i++ ){				// x
			if( i == 0 || i == 7 )
				for( j = 4; j < 7; j++ )		// y
					set_single_led_color( i, j, z, color );
			if( i == 1 || i == 6){
				set_single_led_color( i, 0, z, color );
				set_single_led_color( i, 1, z, color );
				set_single_led_color( i, 4, z, color );
			}
			if( i == 2 || i == 5){
				for( j = 0; j < 7; j++ ){
					if( j != 1 && j != 4 )
						set_single_led_color( i, j, z, color );
				}
			}	
			if( i == 3 || i == 4)
				for( j = 2; j < 6; j++ )
					set_single_led_color( i, j, z, color );
		}
		
}

void danceAlienDown_frame( colorType color ){
	int i, j, z, move_count;	
	z = 0;
	
		// Frame 2
		for( i = 0; i < 8; i++ ){				// x
			if( i == 0 || i == 7 )
				set_single_led_color( i, 0, z, color );
				set_single_led_color( i, 2, z, color );
				set_single_led_color( i, 3, z, color );
			if( i == 1 || i == 6){
				set_single_led_color( i, 0, z, color );
				set_single_led_color( i, 2, z, color_off );
				set_single_led_color( i, 3, z, color );
			}
			if( i == 2 || i == 5){
				for( j = 0; j < 7; j++ ){
					if( j != 3 && j != 7 )		// y
						set_single_led_color( i, j, z, color );
				}
			}	
			if( i == 3 || i == 4)
				for( j = 1; j < 5; j++ )
					set_single_led_color( i, j, z, color );
		}
}
