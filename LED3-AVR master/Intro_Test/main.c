// this program enables SPI communication and
// Sets the AVR into Slave mode

//avrdude -c USBasp -p atmega32 -U flash:w:main.hex

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include <string.h> /* memset */

#define DD_MOSI     PINB3
#define DD_MISO     PINB4

#define DD_SCK      PINB5
#define DDR_SPI     PORTB
typedef enum {
    color_off,
	color_red,
	color_green,
	color_blue,
	color_yellow,
	color_cyan,
	color_pink,
	color_white,
} colorType;


int layer = 0;
int ff = 0;

char layer_select[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

// Buffer --> current_cube (current state)
// [layer(0:7)][rowValue(0:7)]
char current_cube[8][24];
char buffer[8][24];


/*  Color Codes */

/*
 char off[] =  	{ 0x00, 0x00, 0x00 };
 char blue[] = 	{ 0xFF, 0x00, 0x00 };
 char green[] =  { 0x00, 0xFF, 0x00 };
 char red[] =  	{ 0x00, 0x00, 0xFF };
 char yellow[] = { 0x00, 0xFF, 0xFF };
 char cyan[] =  	{ 0xFF, 0xFF, 0x00 };
 char pink[] =  	{ 0xFF, 0x00, 0xFF };
 char white[] =  { 0xFF, 0xFF, 0xFF };
 
 //char rainbow[][] = { off, red, green, blue, yellow, cyan, pink, white };
 
 char color_map[] = {color_off, color_red, color_green, color_blue, color_yellow, color_cyan, color_pink, color_white};
 
 
 
 char *color_map[8];
 color_map[color_off] = off;
 color_map[color_red] = red;
 color_map[color_green] = green;
 color_map[color_blue] = blue;
 color_map[color_cyan] = cyan;
 color_map[color_yellow] = yellow;
 color_map[color_pink] = pink;
 color_map[color_white] = off;*/


//  //////////////////////////////////////////////////////////////////////////////////////  //

void init_ports() {
    MCUCSR = (1<<JTD); // Enable full use of port C by disabling JTAG debugging
    MCUCSR = (1<<JTD); // TODO possibly remove
    
    //MCUCSR = 0;
    
    DDRA = 0xFF; // Make PORTA outputs
    DDRB = 0xFF; // Make PORTB outputs
    DDRC = 0xFF; // Make PORTC outputs
    
    PORTB = 0x00;
}

void init_spi() {
    DDRB &= ~((1<<2)|(1<<3)|(1<<5));   // SCK, MOSI and SS as inputs
    DDRB |= (1<<4);                    // MISO as output
    
    SPCR &= ~(1<<MSTR);                // Set as slave
    SPCR |= (1<<SPE);                  // Enable SPI
    
    DDR_SPI = (1<<DD_MISO);
    
    SPCR = (1<<SPE)|(1<<CPOL)|(1<<SPIE)|(1<<CPHA);      // SPI enable / Clock polarity 1 / SPI interrupts enable
    
    sei();
}

void fire_clock (void) {
    
    PORTB = 1;
    PORTB = 0;
    //_delay_ms(0.01);
}

void all_off() {
    int j = 0;
    PORTC = 0;
    PORTA = 0xFF;
    
    while(j < 24) {
        fire_clock();
        j++;
    }
}

void write(char *d, int data_length, int layer_select_index) {
    int j = 0;
    
    while(j < 24) {
        PORTA = ~d[j];
        fire_clock();
        j++;
    }
	
    PORTC = layer_select[layer_select_index];
    _delay_ms(.2);
    PORTC = 0;
}


void update() {
    memcpy(current_cube, buffer, 192);
}

//  //////////////////////////////////////////////////////////////////////////////////////  //

//  /////////////////////////////////// Main Function ////////////////////////////////////  //
//  //////////////////////////////////////////////////////////////////////////////////////  //

int main (void) {
    
	// Initialize cube
    init_ports();
    //init_spi();
    
	// Copy buffer into current cube
    //update();
    
    int i = 0;
    all_off();
	
	int timer = 0;
    
    while(1) {
        write(current_cube[i], 24, i);
        i = (i + 1) % 8;
		timer++;
		
		// Update cube after 300 writes. (60 ms)
        
        
        
		if( timer >= 300 ){
			intro(color_red);
			timer = 0;
		}
    }
}

//  //////////////////////////////////////////////////////////////////////////////////////  //

ISR (SPI_STC_vect) {
    
    buffer[layer][ff] = SPDR;
    
    ff++;
    update();
    
    
    if(ff == 24) {
        ff = 0;
        layer++;
        if(layer == 8) {
            layer = 0;
            update();
        }
    }
}

//  //////////////////////////////////////////////////////////////////////////////////////  //

// row 7, 6, 5, 4, 3, 2, 1, 0...
// each hex value = B, G, R...
void turnOn( int row, int column, int layer, colorType color ){
	// Interpolate row/column and color combo
	// colors[] = { off, white, pink, cyan, yellow, red, green, blue };
	char onValue[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	
	int i = 8;
	// Turn on column LED
	for( i = (i - 1); i >= 0; )
		if( i != column )
			onValue[i] = onValue[i] || 0;
		else
			onValue[column] = 1;
    
	char colorValue[] = { onValue[7], onValue[6], onValue[5], onValue[4], onValue[3], onValue[2], onValue[1], onValue[0] };
	
	char blue[] = 	{ colorValue, 0x00, 0x00 };
	char green[] =  { 0x00, colorValue, 0x00 };
	char red[] =  	{ 0x00, 0x00, colorValue };
	char yellow[] = { 0x00, colorValue, colorValue };
	char cyan[] =  	{ colorValue, colorValue, 0x00 };
	char pink[] =  	{ colorValue, 0x00, colorValue };
	char white[] =  { colorValue, colorValue, colorValue };
	char off[] =  	{ 0x00, 0x00, 0x00 };
	
	char rowValue[] = { buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7] };
	// Blue, Green, Red
	// Color Test Cases
	
	i = 8;
	for( i = (i - 1); i >= 0; )
		if( i != row ) {
			rowValue[i] = rowValue[i] || off;
        }
		else {
            switch (color) {
                case color_off:
                    rowValue[row] = off;
                    break;
                case color_red:
                    rowValue[row] = red;
                    break;
                case color_green:
                    rowValue[row] = green;
                    break;
                case color_blue:
                    rowValue[row] = blue;
                    break;
                case color_cyan:
                    rowValue[row] = cyan;
                    break;
                case color_yellow:
                    rowValue[row] = yellow;
                    break;
                case color_pink:
                    rowValue[row] = pink;
                    break;
                case color_white:
                    rowValue[row] = white;
                    break;
                default:
                    break;
            }
            
            
            char display[] = { rowValue[7], rowValue[6], rowValue[5], rowValue[4], rowValue[3], rowValue[2], rowValue[1], rowValue[0] };
            
            // Copy display[] to buffer[]
            memcpy(buffer, display, 192);
            
            // Update cube
            update();
            
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
     
     //  //////////////////////////////////////////////////////////////////////////////////////  //
     
     void rainMaker(int maxNumOfDrops, string color){
     // Assuming all new LED's will turn on in layer 7
     int xCord, yCord;
     int last_x, last_y;
     int max = maxNumOfDrops;
     
     if( maxNumOfDrops >= 64 ) max = 64 ;
     int rain = rand()%(max);		// Number of raindrops
     
     for( i = 0; i < rain; i++ ){	// rain = iterations
     xCord = rand()%8;			// x-axis random coordinate
     yCord = rand()%8;			// y-axis random coordinate
     if( xCord != last_x && yCord != last_y ){
     turnON( xCord, yCord, layer_7, color );	// turn-on LED in layer 7
     if( i == (rain - 1) ){		// infinite loop
     layerZDescend();		// Shift all layers down
     delay_ms(wait_long);			// Delay to show rain falling
     
     layerZDescend();		// Shift all layers down
     delay_ms(wait_long);			// Delay to show rain falling
     
     layerZDescend();		// Shift all layers down
     delay_ms(wait_long);			// Delay to show rain falling
     
     i = 0;					// Reset rainCounter
     delay_ms(wait_long);			// Delay to show rain falling
     }
     }
     last_x = xCord;
     last_y = yCord;*/
//}						// end of for loop

}

*/
//  ////////////////////////////////// LED3 Scroll ////////////////////////////////  //

void turnOn_L(int row, colorType color){
    int i = 0;
    for( i = i % 6; i < 6; i++ ){
        int j;
        if( i < 2 ){
            for(j = 2; j < 6; j++ )
                turnOn( row, j, layer_(i+1), color );
        }
        else{
            for(j = 2; j < 4; j++ )
                turnOn( row, j, layer_(i+1), color );
        }
    }
    
} // end function

/*
 void turnOn_E(int row, string color){
 int i = 0;
 for( int i = i % 6; i < 6; i++ ){
 if( i < 2 || i >3){
 for( int j = 2; j < 6; j++ )
 turnOn( row, j, layer_(i+1), color );
 }
 else{
 for( int j = 2; j < 5; j++ )
 turnOn( row, j, layer_(i+1), color );
 }
 }
 } // end function
 
 void turnOn_D(int row, string color){
 int i = 0;
 for( int i = i % 6; i < 6; i++ ){
 if( i == 2 || i == 3){
 for( int j = 2; j < 6; j++ )
 turnOn( row, j, layer_(i+1), color );
 }
 else if( i == 1 || i == 4 ){
 turnOn( row, 2, layer_(i+1), color );
 turnOn( row, 3, layer_(i+1), color );
 turnOn( row, 5, layer_(i+1), color );
 }
 else{
 for( int j = 2; j < 5; j++ )
 turnOn( row, j, layer_(i+1), color );
 }
 }
 } // end function
 
 void turnOn_3(int row, string color){
 int i = 0;
 for( int i = i % 6; i < 6; i++ ){
 if( i < 2 || i >3){
 for( int j = 2; j < 6; j++ )
 turnOn( row, j, layer_(i+1), color );
 }
 else{
 for( int j = 3; j < 6; j++ )
 turnOn( row, j, layer_(i+1), color );
 }
 }
 } // end function
 
 //  ///////////////////////////////// Main Intro() func /////////////////////////////////  //
 
 */
void intro(colorType fontColor) {
    
    int wait_short = 0.2;
    int wait_long = 1;
    colorType rainbow[8] = [ color_off, color_red, color_green, color_blue, color_yellow, color_cyan, color_pink, color_white ];
    
    // Start @ row 0,   finish @ row 7
    // Scroll LED3 from front to back of the cube
    int i;
    for(i = 0; i < 8; i++ ) {
        turnOn_L(i, fontColor);
        //_delay_ms(wait_short);
    }
}
/*
 // Turn off the cube
 all_off();
 delay_ms(wait_long);
 
 for( int i = 0; i < 8; i++ ) {
 turnOn_E(i, fontColor);
 delay_ms(wait_short);
 }
 
 // Turn off the cube
 all_off();
 delay_ms(wait_long);
 
 for( int i = 0; i < 8; i++ ) {
 turnOn_D(i, fontColor);
 delay_ms(wait_short);
 }
 
 // Turn off the cube
 all_off();
 delay_ms(wait_long);
 
 for( int i = 0; i < 8; i++ ) {
 turnOn_3(i, fontColor);
 delay_ms(wait_short);
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
 }*/

//} // End function



