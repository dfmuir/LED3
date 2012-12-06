
#include "buffer.c"


/////////////////////////////////////// Frequency-based animations	///////////////////////////////////////

void center_wave( int low_amp, int mid_amp, int high_amp ){
	int i, j, z;
	
	// Low-pass Frequencies (inner)
	for( j = 0; j < low_amp; j++ )
		for( i = 3; i < 5; i++ )
			for( z = 3; z < 5; z++ )
				set_single_led_color( i, j, z, color_red );
		
	// Band-pass Frequencies (center)
	for( j = 0; j < mid_amp; j++ ){
		for( i = 1; i < 7; i++ ){
			if( i == 2 || i == 5 )
				for( z = 1; z < 7; z++ )
					set_single_led_color( i, j, z, color_green );
			else if( i == 1 || i == 6 ){
				for( z = 1; z < 7; z++ )
					set_single_led_color( i, j-1, z, color_green );
			}
			else{
				set_single_led_color( i, j-1, 1, color_green );
				set_single_led_color( i, j, 2, color_green );
				set_single_led_color( i, j, 5, color_green );
				set_single_led_color( i, j-1, 6, color_green );
			}
		}
	}
	
	// High-pass Frequencies (outter)
	for( j = 0; j < high_amp; j++ ){
		for( i = 0; i < 8; i++ ){
			if( i == 0 || i == 7 )
				for( z = 0; z < 8; z++ )
					set_single_led_color( i, j, z, color_blue );
			else{
				set_single_led_color( i, j, 0, color_blue );
				set_single_led_color( i, j, 7, color_blue );
			}
		}
	}
	
}

////////////////////////   SHIFT EFFECTS   ////////////////////////////


void set_level(char channel, char level) {
    
    char set = (channel == 0)*0x81 + (channel == 1)*0x66 + (channel == 2)*0x18;
    int offset, lev;
    
    
    // Write center two columns
    lev = level;
    
    offset = channel+12;
    buffer[0][offset] = (0 <= lev)*(buffer[0][offset] | set) + (0 > lev)*(buffer[0][offset] & ~set);
    buffer[1][offset] = (1 <= lev)*(buffer[1][offset] | set) + (1 > lev)*(buffer[1][offset] & ~set);
    buffer[2][offset] = (2 <= lev)*(buffer[2][offset] | set) + (2 > lev)*(buffer[2][offset] & ~set);
    buffer[3][offset] = (3 <= lev)*(buffer[3][offset] | set) + (3 > lev)*(buffer[3][offset] & ~set);
    buffer[4][offset] = (4 <= lev)*(buffer[4][offset] | set) + (4 > lev)*(buffer[4][offset] & ~set);
    buffer[5][offset] = (5 <= lev)*(buffer[5][offset] | set) + (5 > lev)*(buffer[5][offset] & ~set);
    buffer[6][offset] = (6 <= lev)*(buffer[6][offset] | set) + (6 > lev)*(buffer[6][offset] & ~set);
    buffer[7][offset] = (7 <= lev)*(buffer[7][offset] | set) + (7 > lev)*(buffer[7][offset] & ~set);
    
    offset = channel+9;
    buffer[0][offset] = (0 <= lev)*(buffer[0][offset] | set) + (0 > lev)*(buffer[0][offset] & ~set);
    buffer[1][offset] = (1 <= lev)*(buffer[1][offset] | set) + (1 > lev)*(buffer[1][offset] & ~set);
    buffer[2][offset] = (2 <= lev)*(buffer[2][offset] | set) + (2 > lev)*(buffer[2][offset] & ~set);
    buffer[3][offset] = (3 <= lev)*(buffer[3][offset] | set) + (3 > lev)*(buffer[3][offset] & ~set);
    buffer[4][offset] = (4 <= lev)*(buffer[4][offset] | set) + (4 > lev)*(buffer[4][offset] & ~set);
    buffer[5][offset] = (5 <= lev)*(buffer[5][offset] | set) + (5 > lev)*(buffer[5][offset] & ~set);
    buffer[6][offset] = (6 <= lev)*(buffer[6][offset] | set) + (6 > lev)*(buffer[6][offset] & ~set);
    buffer[7][offset] = (7 <= lev)*(buffer[7][offset] | set) + (7 > lev)*(buffer[7][offset] & ~set);
    
    
    lev = level >> 1;
    offset = channel+15;
    buffer[0][offset] = (0 <= lev)*(buffer[0][offset] | set) + (0 > lev)*(buffer[0][offset] & ~set);
    buffer[1][offset] = (1 <= lev)*(buffer[1][offset] | set) + (1 > lev)*(buffer[1][offset] & ~set);
    buffer[2][offset] = (2 <= lev)*(buffer[2][offset] | set) + (2 > lev)*(buffer[2][offset] & ~set);
    buffer[3][offset] = (3 <= lev)*(buffer[3][offset] | set) + (3 > lev)*(buffer[3][offset] & ~set);
    buffer[4][offset] = (4 <= lev)*(buffer[4][offset] | set) + (4 > lev)*(buffer[4][offset] & ~set);
    buffer[5][offset] = (5 <= lev)*(buffer[5][offset] | set) + (5 > lev)*(buffer[5][offset] & ~set);
    buffer[6][offset] = (6 <= lev)*(buffer[6][offset] | set) + (6 > lev)*(buffer[6][offset] & ~set);
    buffer[7][offset] = (7 <= lev)*(buffer[7][offset] | set) + (7 > lev)*(buffer[7][offset] & ~set);
    
    offset = channel+6;
    buffer[0][offset] = (0 <= lev)*(buffer[0][offset] | set) + (0 > lev)*(buffer[0][offset] & ~set);
    buffer[1][offset] = (1 <= lev)*(buffer[1][offset] | set) + (1 > lev)*(buffer[1][offset] & ~set);
    buffer[2][offset] = (2 <= lev)*(buffer[2][offset] | set) + (2 > lev)*(buffer[2][offset] & ~set);
    buffer[3][offset] = (3 <= lev)*(buffer[3][offset] | set) + (3 > lev)*(buffer[3][offset] & ~set);
    buffer[4][offset] = (4 <= lev)*(buffer[4][offset] | set) + (4 > lev)*(buffer[4][offset] & ~set);
    buffer[5][offset] = (5 <= lev)*(buffer[5][offset] | set) + (5 > lev)*(buffer[5][offset] & ~set);
    buffer[6][offset] = (6 <= lev)*(buffer[6][offset] | set) + (6 > lev)*(buffer[6][offset] & ~set);
    buffer[7][offset] = (7 <= lev)*(buffer[7][offset] | set) + (7 > lev)*(buffer[7][offset] & ~set);
    
    lev = level >> 2;
    offset = channel+18;
    buffer[0][offset] = (0 <= lev)*(buffer[0][offset] | set) + (0 > lev)*(buffer[0][offset] & ~set);
    buffer[1][offset] = (1 <= lev)*(buffer[1][offset] | set) + (1 > lev)*(buffer[1][offset] & ~set);
    buffer[2][offset] = (2 <= lev)*(buffer[2][offset] | set) + (2 > lev)*(buffer[2][offset] & ~set);
    buffer[3][offset] = (3 <= lev)*(buffer[3][offset] | set) + (3 > lev)*(buffer[3][offset] & ~set);
    buffer[4][offset] = (4 <= lev)*(buffer[4][offset] | set) + (4 > lev)*(buffer[4][offset] & ~set);
    buffer[5][offset] = (5 <= lev)*(buffer[5][offset] | set) + (5 > lev)*(buffer[5][offset] & ~set);
    buffer[6][offset] = (6 <= lev)*(buffer[6][offset] | set) + (6 > lev)*(buffer[6][offset] & ~set);
    buffer[7][offset] = (7 <= lev)*(buffer[7][offset] | set) + (7 > lev)*(buffer[7][offset] & ~set);
    
    offset = channel+3;
    buffer[0][offset] = (0 <= lev)*(buffer[0][offset] | set) + (0 > lev)*(buffer[0][offset] & ~set);
    buffer[1][offset] = (1 <= lev)*(buffer[1][offset] | set) + (1 > lev)*(buffer[1][offset] & ~set);
    buffer[2][offset] = (2 <= lev)*(buffer[2][offset] | set) + (2 > lev)*(buffer[2][offset] & ~set);
    buffer[3][offset] = (3 <= lev)*(buffer[3][offset] | set) + (3 > lev)*(buffer[3][offset] & ~set);
    buffer[4][offset] = (4 <= lev)*(buffer[4][offset] | set) + (4 > lev)*(buffer[4][offset] & ~set);
    buffer[5][offset] = (5 <= lev)*(buffer[5][offset] | set) + (5 > lev)*(buffer[5][offset] & ~set);
    buffer[6][offset] = (6 <= lev)*(buffer[6][offset] | set) + (6 > lev)*(buffer[6][offset] & ~set);
    buffer[7][offset] = (7 <= lev)*(buffer[7][offset] | set) + (7 > lev)*(buffer[7][offset] & ~set);

    
    lev = level >> 8;
    offset = channel+21;
    buffer[0][offset] = (0 <= lev)*(buffer[0][offset] | set) + (0 > lev)*(buffer[0][offset] & ~set);
    buffer[1][offset] = (1 <= lev)*(buffer[1][offset] | set) + (1 > lev)*(buffer[1][offset] & ~set);
    buffer[2][offset] = (2 <= lev)*(buffer[2][offset] | set) + (2 > lev)*(buffer[2][offset] & ~set);
    buffer[3][offset] = (3 <= lev)*(buffer[3][offset] | set) + (3 > lev)*(buffer[3][offset] & ~set);
    buffer[4][offset] = (4 <= lev)*(buffer[4][offset] | set) + (4 > lev)*(buffer[4][offset] & ~set);
    buffer[5][offset] = (5 <= lev)*(buffer[5][offset] | set) + (5 > lev)*(buffer[5][offset] & ~set);
    buffer[6][offset] = (6 <= lev)*(buffer[6][offset] | set) + (6 > lev)*(buffer[6][offset] & ~set);
    buffer[7][offset] = (7 <= lev)*(buffer[7][offset] | set) + (7 > lev)*(buffer[7][offset] & ~set);
    
    offset = channel+0;
    buffer[0][offset] = (0 <= lev)*(buffer[0][offset] | set) + (0 > lev)*(buffer[0][offset] & ~set);
    buffer[1][offset] = (1 <= lev)*(buffer[1][offset] | set) + (1 > lev)*(buffer[1][offset] & ~set);
    buffer[2][offset] = (2 <= lev)*(buffer[2][offset] | set) + (2 > lev)*(buffer[2][offset] & ~set);
    buffer[3][offset] = (3 <= lev)*(buffer[3][offset] | set) + (3 > lev)*(buffer[3][offset] & ~set);
    buffer[4][offset] = (4 <= lev)*(buffer[4][offset] | set) + (4 > lev)*(buffer[4][offset] & ~set);
    buffer[5][offset] = (5 <= lev)*(buffer[5][offset] | set) + (5 > lev)*(buffer[5][offset] & ~set);
    buffer[6][offset] = (6 <= lev)*(buffer[6][offset] | set) + (6 > lev)*(buffer[6][offset] & ~set);
    buffer[7][offset] = (7 <= lev)*(buffer[7][offset] | set) + (7 > lev)*(buffer[7][offset] & ~set);
    
}



/* WORKING
void set_level(char channel, char level) {
    
    char set = 0;
    int offset = 0;
    if(channel == 0) {
        set = 0x81;
        offset = 0;
    }
    else if(channel == 1) {
        set = 0x66;
        offset = 1;
    }
    else if(channel == 2) {
        set = 0x18;
        offset = 2;
    }
    
    
    int i;
    for(i = 0; i <= level; i++) {
        buffer[i][offset] |= set;
    }
    for(i = level+1; i < 8; i++) {
        buffer[i][offset] &= ~set;
    }
}

 


void set_level(char channel, char level) {
    
    int row_offset;
    for(row_offset = 4*3; row_offset < 5*3; row_offset+=3) {
    
        int offset = 0;
        if(channel == 0) {
            int set = 0x81;
            int offset = 0 + row_offset;
            
            int i;
            for(i = 0; i <= level; i++) {
                buffer[i][offset+row_offset] |= set;
            }
            for(i = level+1; i < 8; i++) {
                buffer[i][offset] &= ~set;
            }
            
            
        }
        else if(channel == 1) {
            int set_blue = 0x66;
            int set_green = 0x42;
            int offset = 1 + row_offset;
            
            int i;
            for(i = 0; i <= level; i++) {
                buffer[i][offset] |= set_blue;
                buffer[i][offset-1] |= set_green;
            }
            for(i = level+1; i < 8; i++) {
                buffer[i][offset] &= ~set_blue;
                buffer[i][offset-1] &= ~set_green;
            }
            
            
        }
        else if(channel == 2) {
            int set = 0x18;
            int offset = 2 + row_offset;
            
            int i;
            for(i = 0; i <= level; i++) {
                buffer[i][offset] |= set;
            }
            for(i = level+1; i < 8; i++) {
                buffer[i][offset] &= ~set;
            }
        }
    }
}


void set_level(char channel, char level) {
    
    int z;
    for(z = 0; z <=level; z++) {
        if(channel = 0)
            buffer[z][9] = ;
        
    }
}
*/




void shift_top_to_bottom(int num_shifts){
	int i;
	for( i = 0; i < 7; i++ ) {
		memcpy(buffer[i], buffer[i+1], 24);
    }
    /*
    int x,z;
    for(x=0; x<8; x++) {
        for(z=0; z<8; z++) {
            set_single_led_color(x,7,z,0);
        }

    }*/
    
    for(i=0; i<24; i++) {
        buffer[7][i] = 0;
    }
}

void shift_front_to_back() {
    int x, y, z;
    for(z=0; z<8; z++) {
        for(x=0; x<8; x++) {
            for(y=0; y<8; y++) {
                set_single_led_color(x,y,z+1,color_for_led(x,y,z));
            }
        }
    }
    for(x=0; x<8; x++) {
        for(y=0; y<8; y++) {
            set_single_led_color(x,y,0,color_off);
        }
    }
}


void rotate_left() {
    int x, y, z;
    
    for(y=0; y<8; y++) {
        
        
        //Ditched loops to improve performance

        set_single_led_color(7,y,0,color_for_led(7,y,1));
        set_single_led_color(7,y,1,color_for_led(7,y,2));
        set_single_led_color(7,y,2,color_for_led(7,y,3));
        set_single_led_color(7,y,3,color_for_led(7,y,4));
        set_single_led_color(7,y,4,color_for_led(7,y,5));
        set_single_led_color(7,y,5,color_for_led(7,y,6));
        set_single_led_color(7,y,6,color_for_led(7,y,7));
        
        
        set_single_led_color(7,y,7,color_for_led(6,y,7));
        set_single_led_color(6,y,7,color_for_led(5,y,7));
        set_single_led_color(5,y,7,color_for_led(4,y,7));
        set_single_led_color(4,y,7,color_for_led(3,y,7));
        set_single_led_color(3,y,7,color_for_led(2,y,7));
        set_single_led_color(2,y,7,color_for_led(1,y,7));
        set_single_led_color(1,y,7,color_for_led(0,y,7));
        
        set_single_led_color(0,y,7,color_for_led(0,y,6));
        set_single_led_color(0,y,6,color_for_led(0,y,5));
        set_single_led_color(0,y,5,color_for_led(0,y,4));
        set_single_led_color(0,y,4,color_for_led(0,y,3));
        set_single_led_color(0,y,3,color_for_led(0,y,2));
        set_single_led_color(0,y,2,color_for_led(0,y,1));
        set_single_led_color(0,y,1,color_for_led(0,y,0));

        set_single_led_color(0,y,0,color_for_led(1,y,0));
        set_single_led_color(1,y,0,color_for_led(2,y,0));
        set_single_led_color(2,y,0,color_for_led(3,y,0));
        set_single_led_color(3,y,0,color_for_led(4,y,0));
        set_single_led_color(4,y,0,color_for_led(5,y,0));
        set_single_led_color(5,y,0,color_for_led(6,y,0));
        set_single_led_color(6,y,0,color_for_led(7,y,0));


        /*
        for(z=0; z<8; z++) {
            set_single_led_color(7,y,z,color_for_led(7,y,z+1));
        }
        
        for(x = 7; x>0; x--){
            set_single_led_color(x,y,7,color_for_led(x-1,y,7));
        }

        
        for(z = 7; z>0; z--){
            set_single_led_color(0,y,z,color_for_led(0,y,z-1));
        }
        
        for(x=0; x<8; x++) {
            set_single_led_color(x,y,0,color_for_led(x+1,y,0));
        }*/
    }
}


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

void letter_small3(int row, colorType color){
	set_single_led_color( 4, 3, row, color );
	set_single_led_color( 4, 7, row, color );
	set_single_led_color( 5, 3, row, color );
	set_single_led_color( 5, 5, row, color );
	set_single_led_color( 5, 7, row, color );
	set_single_led_color( 6, 4, row, color );
	set_single_led_color( 6, 6, row, color );
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

void rainbowRainMaker_frame(int maxNumOfDrops){
	// Assuming all new LED's will turn on in layer 7
	int xCord, zCord;
	int max = maxNumOfDrops;

	if( maxNumOfDrops >= 64 ) max = 64 ;
	int rain = rand()%(max);		// Number of raindrops

	int i, rainbow;
	for( i = 0; i < rain; i++ ){				// rain = iterations
		xCord = rand()%8;			// x-axis random coordinate 
		zCord = rand()%8;			// y-axis random coordinate
		rainbow = rand()%8;			// Random color
        set_single_led_color( xCord, 7, zCord, rainbow );		// turn-on LED in layer 7
    }						// end of for loop
}

void danceAlienUp_frame( colorType color ){
	int i, j, z, move_count;	
	for( z = 0; z < 8; z++ ){
		if( z == 3 || z == 4){
			// Frame 1
			for( i = 0; i < 8; i++ ){				// x
				if( i == 0 || i == 7 )
					for( j = 4; j < 7; j++ ){		// y
						if( j == 6 )
							set_single_led_color( i, j, z, color_white );
						else
							set_single_led_color( i, j, z, color );
					}
				if( i == 1 || i == 6){
					set_single_led_color( i, 0, z, color );
					set_single_led_color( i, 1, z, color );
					set_single_led_color( i, 4, z, color );
				}
				if( i == 2 || i == 5){
					for( j = 0; j < 8; j++ ){
						if( j == 0 )
							set_single_led_color( i, j, z, color_white );							
						else if( j != 1 && j != 4 )
							set_single_led_color( i, j, z, color );
					}
				}	
				if( i == 3 || i == 4)
					for( j = 2; j < 6; j++ )
						set_single_led_color( i, j, z, color );
			}
		}
		if( z == 2 || z == 5 ){
			for( i = 0; i < 8; i++ ){
				// Fingers
				if( i == 0 || i == 7 ){
					set_single_led_color( i, 5, z, color );	
					set_single_led_color( i, 6, z, color_white );	
				}
				// Toes
				if( i == 2 || i == 5 ){
					set_single_led_color( i, 0, z, color_white );		
					set_single_led_color( i, 5, z, color );		
					set_single_led_color( i, 6, z, color );							
					set_single_led_color( i, 7, z, color );				
					
				}				
				if( i == 3 || i == 4 ){
					set_single_led_color( i, 2, z, color );
					set_single_led_color( i, 3, z, color );
					set_single_led_color( i, 5, z, color );	
					set_single_led_color( i, 7, z, color );	
				}
			}
			// Eyes
			if( z == 2 ){
				set_single_led_color( 3, 6, z, color_white );	
				set_single_led_color( 4, 6, z, color_white );	
			}
			else{
				set_single_led_color( 3, 6, z, color );	
				set_single_led_color( 4, 6, z, color );	
			}
		}
	}
}

void danceAlienDown_frame( colorType color ){
	int i, j, z, move_count;	
	for( z = 0; z < 8; z++ ){
		if( z == 3 || z == 4 ){
			// Frame 2
			for( i = 0; i < 8; i++ ){				// x
				if( i == 0 || i == 7 ){
					set_single_led_color( i, 0, z, color_white );
					set_single_led_color( i, 2, z, color_white );
					set_single_led_color( i, 3, z, color );
				}
				if( i == 1 || i == 6){
					set_single_led_color( i, 0, z, color );
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
		if( z == 2 || z == 5 ){
			for( i = 0; i < 8; i++ ){
				// Toes and Fingers
				if( i == 0 || i == 7 ){
					set_single_led_color( i, 0, z, color_white );	
					set_single_led_color( i, 2, z, color_white );	
				}
				if( i == 2 || i == 5 ){
					set_single_led_color( i, 4, z, color );	
					set_single_led_color( i, 5, z, color );	
					set_single_led_color( i, 6, z, color );	
				}
				if( i == 3 || i == 4 ){
					set_single_led_color( i, 1, z, color );
					set_single_led_color( i, 2, z, color );
					set_single_led_color( i, 4, z, color );	
					set_single_led_color( i, 6, z, color );	

				}
			}
			// Eyes
			if( z == 2 ){
				set_single_led_color( 3, 5, z, color_white );	
				set_single_led_color( 4, 5, z, color_white );	
			}
			else{
				set_single_led_color( 3, 5, z, color );	
				set_single_led_color( 4, 5, z, color );	
			}
		}
	}
}

// PICTURES


void four_cubes(){
	clear_buffer();
	
	// 2 x 2
	create_cube_outline(3, 3, 3, 4, 4, 4, color_white);
	
	// 4 x 4
	create_cube_outline(2, 2, 2, 5, 5, 5, color_blue);
    
	// 6 x 6
	create_cube_outline(1, 1, 1, 6, 6, 6, color_green);
    
	// 8 x 8
	create_cube_outline(0, 0, 0, 7, 7, 7, color_red);
    
	
	update();
}

void letter_Aplus( colorType color ){
	clear_buffer();
	int i, j, z;
	for( z = 0; z < 8; z++ ){
		if( z == 3 || z == 4 ){
			for( i = 0; i < 8; i++ ){
				if( i == 0 || i == 3 ){
					for( j = 0; j < 6; j++ )
						set_single_led_color( i, j, z, color );
				}
				else if( i == 1 || i == 2 ){
					set_single_led_color( i, 3, z, color );
					set_single_led_color( i, 6, z, color );
				}
				else if( i == 5 || i == 7 )
					set_single_led_color( i, 3, z, color_white );
				else if( i == 6 ){
					set_single_led_color( i, 2, z, color_white );
					set_single_led_color( i, 3, z, color_white );
					set_single_led_color( i, 4, z, color_white );
				}
			}
		}
		if( z == 2 || z == 5 ){
			for( i = 0; i < 7; i++ ){
				if( i == 0 || i == 3 ){
					for( j = 0; j < 6; j++ )
						set_single_led_color( i, j, z, color );
				}
				else if( i == 1 || i == 2 ){
					set_single_led_color( i, 3, z, color );
					set_single_led_color( i, 6, z, color );
				}
				else if( i == 6 )
					set_single_led_color( i, 3, z, color_white );
			}
		}
	}
}

void flag(){
	clear_buffer();
	int i, j, z;
	for( z = 0; z < 8; z++ ){
		if( z == 3 || z == 4 ){
			for( j = 0; j < 8; j++ ){
				if( j == 0 || j == 2 ){
					for( i = 0; i < 8; i++ )
						set_single_led_color( i, j, z, color_white );
				}
				else if( j == 1 || j == 3 ){
					for( i = 0; i < 8; i++ )
						set_single_led_color( i, j, z, color_red );
				}
				else if( j == 4 || j == 6){
						set_single_led_color( 0, j, z, color_white );
						set_single_led_color( 1, j, z, color_blue );
						set_single_led_color( 2, j, z, color_white );
						set_single_led_color( 3, j, z, color_blue );

					for( i = 4; i < 8; i++ )
						set_single_led_color( i, j, z, color_white );
				}
				else{
						set_single_led_color( 0, j, z, color_blue );
						set_single_led_color( 1, j, z, color_white );
						set_single_led_color( 2, j, z, color_blue );
						set_single_led_color( 3, j, z, color_white );

					for( i = 4; i < 8; i++ )
						set_single_led_color( i, j, z, color_red );
				}
			}
		}
	}
}

void bluebox() {
    clear_buffer();
    create_cube_outline(2,2,2,5,5,5,color_blue);
}
