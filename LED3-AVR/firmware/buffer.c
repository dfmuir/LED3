#include "colorType.h"

colorType color = color_cyan;

void set_single_led_color( int x, int y, int z, colorType color ) {
        
    int red = (color==color_red) || (color==color_pink) || (color==color_yellow) || (color==color_white);
    int green = (color==color_green) || (color==color_cyan) || (color==color_yellow) || (color==color_white);
    int blue = (color==color_blue) || (color==color_pink) || (color==color_cyan) || (color==color_white);
    
    if(red) buffer[y][23-((z*3))] |= (1 << x); // RED
    else buffer[y][23-((z*3))] &= ~(1 << x);
    
    if(green) buffer[y][22-((z*3))] |= (1 << x); // GREEN
    else buffer[y][22-((z*3))] &= ~(1 << x);
    
    if(blue) buffer[y][21-((z*3))] |= (1 << x); // BLUE
    else buffer[y][21-((z*3))] &= ~(1 << x);

}

colorType color_for_led(int x, int y, int z) {
    

    
    int red   =  ((buffer[y][23-((z*3))]) >> x) & 1; // RED
    int green =  ((buffer[y][22-((z*3))]) >> x) & 1; // GREEN
    int blue  =  ((buffer[y][21-((z*3))]) >> x) & 1; // BLUE
    
    
    
    if(!red && !green && !blue) {
        return color_off;
    }
    else if(red && !green && !blue) {
        return color_red;
    }
    else if(!red && green && !blue) {
        return color_green;
    }
    else if(!red && !green && blue) {
        return color_blue;
    }
    else if(red && green && !blue) {
        return color_yellow;
    }
    else if(red && !green && blue) {
        return color_pink;
    }
    else if(!red && green && blue) {
        return color_cyan;
    }
    else if(red && green && blue) {
        return color_white;
    }
    return color_off;
    
}

void clear_buffer() {
    int layer;
    for(layer = 0; layer < 8; layer++) {
        int ff;
        for(ff = 0; ff < 24; ff++) {
            buffer[layer][ff] = 0;
        }
    }
}



