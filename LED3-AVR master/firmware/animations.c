#include "frames.c"
#include "animator.c"



void diagonal(count) {
    clear_buffer();
    set_single_led_color(count%8,count%8,count%8,color_blue);
    update();
}

void face(count) {
    clear_buffer();
    set_single_led_color(count%8,7,count%8,color_red);
    update();
}


void grow_cube(count) {
    clear_buffer();
    
    
    colorType color = (int)(count/16)+1;
    
    int c = count%32;
    
    if(c < 8) {
        create_cube_outline(0, 0, 0, count%8, count%8, count%8, color);
    }
    else if(c < 16) {
        create_cube_outline(count%8, count%8, count%8, 7,7,7, color);

    }
    else if(c < 24) {
        create_cube_outline(7-count%8, 7-count%8, 7-count%8, 7,7,7, color);

    }
    else {
        create_cube_outline(0,0,0, 7-count%8, 7-count%8, 7-count%8, color);
    }
    
    
    
    update();
}




void led3(count) {
    
    /*
    if(count%8 == 0) {
        letter_L(0, color_cyan);
    }
    else {
        //shift_front_to_back();
    }
    
    */
    clear_buffer();
    if(count >= 0 && count < 24/3)
        letter_L(7-count%8, color_cyan);
    else if(count >=24/3 && count < 48/3) {
        letter_E(7-count%8, color_green);
    }
    else if(count >=48/3 && count < 72/3) {
        letter_D(7-count%8, color_red);
    }
    else if(count >=72/3 && count < 96/3) {
        letter_3(7-count%8, color_pink);

    }
    update();
}

void led3_blue(count) {
    
    /*
     if(count%8 == 0) {
     letter_L(0, color_cyan);
     }
     else {
     //shift_front_to_back();
     }
     
     */
    clear_buffer();
    if(count >= 0 && count < 24/3)
        letter_L(7-count%8, color_blue);
    else if(count >=24/3 && count < 48/3) {
        letter_E(7-count%8, color_blue);
    }
    else if(count >=48/3 && count < 72/3) {
        letter_D(7-count%8, color_blue);
    }
    else if(count >=72/3 && count < 96/3) {
        letter_3(7-count%8, color_blue);
        
    }
    update();
}

void led3_rotate(count) {
    
    rotate_left();

    if(count==0) {
        letter_L(0, color_red);
    }
    else if(count==7) {
        letter_E(0, color_green);

    }
    else if(count==14) {
        letter_D(0, color_blue);
    }
    else if(count==18) {
        letter_small3(0, color_white);
    }


    update();
}

void rainMaker(count) {
        
    int c = count%2;
	int random;
	
	// Make rain (rainbow layers)
    shift_top_to_bottom(1);

    if( c == 0 ) {
		random = rand()%8;
        
        colorType pallette[] = {color_blue, color_white, color_cyan};
        int color_rand = rand()%3;
        
		rainMaker_frame( 10, pallette[color_rand]);
	}

    update();
}

void rainbowRainMaker(count) {
    
    int c = count%2;
	
	// Make rain (rainbow layers)
    shift_top_to_bottom(1);

    if( c == 0 )
		rainbowRainMaker_frame( 10 );
	
    update();
}

void danceAlien(count) {    
    clear_buffer();
    
	int random;
	
	// Make rain (rainbow layers)
    //shift_top_to_bottom(1);

    if(count%2 == 0) {
		danceAlienUp_frame( color_red );
	}
	else {
		danceAlienDown_frame( color_red );
    }

	
    update();
}

