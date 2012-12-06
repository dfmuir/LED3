// this program enables SPI communication and
// Sets the AVR into Slave mode


//avrdude -c USBasp -p atmega32 -U flash:w:main.hex

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>




int layer_select[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
//int layer_select[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


//char data

void fire_clock (void) {
    

    PORTB = 0;

    PORTB = 1;
    _delay_ms(.0001);
    //_delay_ms(1);
    PORTB = 0;
    
    
}

void write(char *d, int data_length, int layer_select_index) {
    int j = 0;
    
    while(j < data_length) {
        PORTA = ~d[j];
        fire_clock();
        
        j++;
    }
    

    
}

int* exclude145(int *d) {

    d[9] = 0;
    d[10] = 0;
    d[11] = 0;
    
    d[12] = 0;
    d[13] = 0;
    d[14] = 0;
    
    d[18] = 0;
    d[19] = 0;
    d[20] = 0;
    
    d[21] = 0;
    d[22] = 0;
    d[23] = 0;

    
    return d;

}

int main (void) {
    
    char data[] = {0x0F, 0x01, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x10, 0xFF, 0xFF, 0x10, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x01};
    char data2[] = {0x0F, 0x01, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x08, 0x01, 0xFF, 0xFF, 0x01, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x80};
    
    
    
    
    char data3[] = {0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00};
    
    //int layer_select[] = {0, 0, 0x04, 0, 0, 0, 0, 0};

    char data4[] = {0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF};
    
    char blue[] = { 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00};

    char red[] =  {0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,  0x00, 0x00, 0xFF,  0x00, 0x00, 0xFF,  0x00, 0x00, 0xFF,  0x00, 0x00, 0xFF,  0x00, 0x00, 0xFF};
    
    char green[] =  { 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,  0x00, 0x00, 0xFF,  0x00, 0x00, 0xFF,  0x00, 0x00, 0xFF,  0x00, 0x00, 0xFF,  0x00, 0x00, 0xFF, 0x00};
    
    char yellow[] =  { 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF, 0xFF};
    
    char cyan[] =  { 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF, 0xFF, 0x00};
    
    char pink[] =  { 0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF,  0xFF, 0x00, 0xFF};
    
    char white[] =  { 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF};

    
    char test[] =  { 0, 0, 0xFF,  0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0,  0xff, 0xff, 0,  0xff, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF,  0x00, 0xFF, 0xFF};
    
    //int test2[] = { 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0,  0x00, 0x00, 0,  0x00, 0x00, 0xFF,  0x00, 0x00, 0xFF,  0x00, 0x00, 0xFF,  0x00, 0x00, 0xFF, 0x00};

    char test2[] = { 0x00, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0,  0, 0x00,  0x00, 0xFF, 0xFF, 0xFF,  0xFF, 0x00, 0x00,  0xFF, 0x00, 0x00,  0xFF, 0x00, 0x00, 0xFF, 0x00};



    
    
    char row4_data = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    
    
    MCUCSR = (1<<JTD); // Enable full use of port C by disabling JTAG debugging
    MCUCSR = (1<<JTD); // TODO possibly remove
    
    
    //DDRD = 0xFF;           /* make the LED pin an output */
    DDRA = 0xFF;
    DDRB = 0xFF;
    DDRC = 0xFF;
    
    int fData[24];
    int k = 0;
    while (k < 24) {
        fData[k] = 0xFF;
        k++;
    }

    int i = 0;
    
    int someData [24];
    someData[0] = 0xff;
    someData[1] = 0xff;
    someData[2] = 0xff;
    
    int p = 0;
    
    
    int y = 0;
    
    //write(yellow, 24, i);

    int j;
    while(1) {
        char * color;
        
        if (j == 6000) color = white;
        if (j == 12000) color = blue;
        if (j == 18000) {
            color = pink;
            j = 0;
        }
        
        j++;
//        if (i % 2 == 0) {
//            write(fData, 24, i);
//        }
//        else {
//            write(fData, 24, i);
        
        //PORTA = 0;
        write(color, 24, i);
        
        PORTC = layer_select[i];
        _delay_ms(.1);
        PORTC = 0;
//        }
        i = (i + 1) % 8;
        
    }
    

}
    
    
    /*
    
    
    
    int i =0;
    while(1) {
    
//       
        
        int k = 0;
        while (k < 8) {
            int j = 0;
            
            while (j < 3) {
                switch (j) {
                    //R
                    case 0:
                        PORTA = 0x00;
                        fire_clock();
                        break;
                    //G
                    case 1:
                        PORTA = 0xFF;
                        fire_clock();
                        break;
                    //B
                    case 2:
                        PORTA = 0xFF;
                        fire_clock();
                        break;
                        
                    default:
                        break;
                }
                j++;
            }
            
            k++;
        }
        
        PORTC = layer_select[i];
        i = (i + 1) % 8;

        
        _delay_ms(0.1);
        
        PORTC = 0;
        
    }
    
    

    
    
}


    
    /*
    PORTA = ~0x00;
    _delay_ms(7);
    
    fire_clock();
    
    PORTA = ~0x01;
    _delay_ms(7);
    
    fire_clock();
    
    PORTA = ~0x02;
    _delay_ms(7);
    
    fire_clock();
    
    PORTA = ~0x04;
    _delay_ms(7);
    
    fire_clock();
    
    PORTA = ~0x08;
    _delay_ms(7);
    
    fire_clock();
    
    PORTA = ~0x10;
    _delay_ms(7);
    
    fire_clock();
    
    PORTA = ~0x20;
    _delay_ms(7);
    
    fire_clock();
    
    PORTA = ~0x40;
    _delay_ms(7);
    
    fire_clock();
    
    PORTA = ~0x80;
    _delay_ms(7);
    
    
    fire_clock();
    
    
    while(1) {
    
        
        
    }
    
    

    
    
    

}


void fire_clock (void) {
    PORTB = 0;
    PORTB = 1;
    PORTB = 0;
}


    /*
    
    DDRB &= ~((1<<2)|(1<<3)|(1<<5));   // SCK, MOSI and SS as inputs
    DDRB |= (1<<4);                    // MISO as output
    
    SPCR &= ~(1<<MSTR);                // Set as slave
    SPCR |= (1<<SPE);                  // Enable SPI
        
    DDR_SPI = (1<<DD_MISO);
    
    SPCR = (1<<SPE)|(1<<CPOL)|(1<<SPIE)|(1<<CPHA);      // SPI enable / Clock polarity 1 / SPI interrupts enable
    
    sei();
    
    while(1)
    {
        ;
    }
     
     
}

ISR (SPI_STC_vect)                         // Interrupt on Int0 vector

{
    
    data = SPDR;
    PORTC = data;

    //PORTC = SPDR;

    
    PORTD = 0x00;
    _delay_ms(10);
    PORTD = 0xFF;
    
    
}

*/