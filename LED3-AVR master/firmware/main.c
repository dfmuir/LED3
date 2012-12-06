// this program enables SPI communication and
// Sets the AVR into Slave mode

//avrdude -c USBasp -p atmega32 -U flash:w:main.hex

#include <avr/interrupt.h>
#include <avr/delay.h>
#include <string.h> /* memset */

#include "init.c"
//#include "refresh.c"
//#include "launcher.c"
//#include "interrupts.c"

int main (void) {
    
    
    char america7[] =  { 0xF0, 0x50, 0x5F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    char america6[] =  { 0xFF, 0xAF, 0xAF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    char america5[] =  { 0xF0, 0x50, 0x5F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    char america4[] =  { 0xFF, 0xAF, 0xAF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    char america3[] =  { 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    char america2[] =  { 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    char america1[] =  { 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    char america0[] =  { 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    
    
    init_spi();
    
    
    while(1) {
    SPI_MasterTransmit(0xFF);
        for(int i = 0; i <192; i++) {
            SPI_MasterTransmit(0xFF);
        }
    }
    
    
    //init_ports();
    //init_spi();
    //init_animation_timer();
    
    //launch_rainMaker();
	//launch_rainbowRainMaker();
    //launch_bluebox();
    //launch_diagonal();
    //launch_grow_cube();
    //launch_led3_front_to_back();
    //launch_led3_rotate();
    //create_cube_outline(2,2,2,4,color_blue);
    //create_cube(0,0,0,8,color_blue, color_off);

    //launch_danceAlien();
    
    //create_cube(1,1,1,6,color_green, color_off);
    
    //launch_four_cubes();
	//launch_tesseract();
	//launch_flag();
	//launch_Aplus();
    
    //create_cube_outline(0,0,0,7,7,7,color_blue);

    
    //update();
    //start_cube();
    
    
    
    
    return 1;
}

void SPI_MasterTransmit(char cData) {
    /* Start transmission */
    SPDR = cData;
    /* Wait for transmission complete */ while(!(SPSR & (1<<SPIF)));
}

/*

 void layerZDescend(){
 char firstLayer[24] = buffer[0];
 for( int i = 0; i<8; i++ ){
 if( i == 7 )
 buffer[i] = firstLayer;
 else
 buffer[i] = buffer[i+1];
 }
 
 // Update cube
 update();
 }
 
//  ////////////////////////////////// LED3 Scroll ////////////////////////////////  //



//  ///////////////////////////////// Main Intro() func /////////////////////////////////  //

     

void intro(colorType fontColor) {
    
    //colorType rainbow[] = { color_off, color_red, color_green, color_blue, color_yellow, color_cyan, color_pink, color_white };
    
    //clear_buffer();
    //update();
    // Start @ row 0,   finish @ row 7
    // Scroll LED3 from front to back of the cube
    int i;
    for(i = 0; i < 8; i++ ) {
        turnOn_L(i, color_white);
    }
    update();

 // Turn off the cube
 clear_buffer();
 
 for( i = 0; i < 8; i++ ) {
 turnOn_E(i, color_green);
 }
    update();
    
 
 // Turn off the cube
 clear_buffer();
 
 for( i = 3; i < 5; i++ ) {
 turnOn_3(i, color_pink);
 }
    
    update();
    
}
 
 // Turn off the cube
 clear_buffer();
 _delay_ms(wait_long);
 
 for( i = 0; i < 8; i++ ) {
 turnOn_3(i, fontColor);
 _delay_ms(wait_short);
 }
 }
 
 
 
 // Turn off the cube
 all_off();
 delay_ms(wait_long);
 delay_ms(wait_long);
 delay_ms(wait_long);
 
 // 4 rainfalls
 for( int i = 0; i < 5; i++ )
 rainMaker(48, rainbow[rand()%8]);
 
 // Let rain finish falling to the ground
 for( int i = 0; i < 4; i++ )
 layerZDescend();
 
 // Turn off the cube
 all_off();
 delay_ms(wait_long);
 
 // Flash through all color combinations
 for( int i = 0; i < 8; i++ ){				// color
 for( int j = 0; j < 8; j++ )			// layer
 for( int k = 0; k < 8; k++ )		// row
 for( int l = 0; l < 8; l++ )	// column
 // Change column, then row, then layer, then color.
 turnOn( k, l, j, rainbow[i]);
 // Wait between color changes.
 delay_ms(wait_long);
 }
 
 // Turn off the cube
 all_off();
 
 // White Boxframe
 for( int i = 0; i < 8; i++ ){				// color
 for( int j = 0; j < 8; j++ ){			// layer
 if( j == 0 || j == 7 ){					// top and bottom layer
 for( int k = 0; k < 8; k++ ){		// row
 if( k == 0 || k == 7 )				// front and back row
 for( int l = 0; l < 8; l++ )	// column
 turnOn( k, l, j, white );
 else								// all other rows (1:6)
 for( int l = 0; l < 8; l+7 )
 turnOn( k, l, j, white );
 }
 }
 else{
 for( int k = 0; k < 8; k++ ){		// row
 if( k == 0 || k == 7 )			// front and back row
 for( int l = 0; l < 8; l+7 )
 turnOn( k, l, j, white );	// turn on corner LEDs
 }
 }
 }
 
 // Wait/ Hold
 delay_ms(wait_long);
 delay_ms(wait_long);
 delay_ms(wait_long);
 delay_ms(wait_long);
 delay_ms(wait_long);
 }

*/
//} // End function



