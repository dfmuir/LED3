// this program enables SPI communication and
// Sets the AVR into Slave mode


//avrdude -c USBasp -p atmega32 -U flash:w:main.hex

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

#define DD_MOSI     PINB3
#define DD_MISO     PINB4

#define DD_SCK      PINB5
#define DDR_SPI     PORTB


char *data;
char *buffer;

char layer_select[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};


/*              */

char blue[] = { 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00};

char red[] =  {0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,  0x00, 0x00, 0xFF,  0x00, 0x00, 0xFF,  0x00, 0x00, 0xFF,  0x00, 0x00, 0xFF,  0x00, 0x00, 0xFF};

char green[] =  { 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,  0x00, 0x00, 0xFF,  0x00, 0x00, 0xFF,  0x00, 0x00, 0xFF,  0x00, 0x00, 0xFF,  0x00, 0x00, 0xFF, 0x00};

char yellow[] =  { 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF, 0xFF};

char cyan[] =  { 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF, 0xFF, 0x00};

char pink[] =  { 0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF};

char white[] =  { 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF};

char test[] =  { 0xFF, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0};

char off[] =  { 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0};



/*              */


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
    //_delay_ms(.00005);
    PORTB = 1;
    _delay_ms(.00001);
    PORTB = 0;
    
    
}

void all_off() {
    int j = 0;
    PORTC = 0;
    PORTA = 0xFF;

    while(j < 24) {
        fire_clock();
        j++;
    }
    
    //PORTA = 0;
}

void write(char *d, int data_length, int layer_select_index) {
    int j = 0;
    
    //if(layer_select_index <= 4) {
        
    //}



    PORTC = layer_select[layer_select_index];

    
    while(j < 24) {
        PORTA = ~d[j];
        fire_clock();
        
        j++;
    }

    
    
    //PORTA = 0;
    
//    if(layer_select_index < 4) {
//        PORTC = layer_select[layer_select_index];
//        
    //}



    _delay_ms(.175);
    PORTC = 0;
    
}






int main (void) {
    
    //int current_byte = 0;
    
    init_ports();
    //init_spi();
    
    //PORTC = 0x80;
    
    int i = 0;

    all_off();

    
    int p = 0;
    while(1) {
        
        if(p > 0 && p < 2000) write(blue, 24, i);
        if(p > 2000 && p < 4000) write(cyan, 24, i);
        if(p > 4000 && p < 6000) write(red, 24, i);
        if(p > 6000 && p < 8000) write(green, 24, i);
        if(p > 8000 && p < 10000) write(yellow, 24, i);
        if(p > 10000 && p < 14000) write(pink, 24, i);
        if(p > 14000 && p < 18000) write(white, 24, i);

//        write(yellow, 24, i);
//        write(blue, 24, i);
//        write(yellow, 24, i);
//        write(pink, 24, i);
//        write(cyan, 24, i);
//        write(white, 24, i);
//        all_off();
        
        p+=10;


        i = (i + 1) % 8;
        
    }
}



ISR (SPI_STC_vect) {                       // Interrupt on Int0 vector
    //buffer[current_byte] = SPDR;
}




