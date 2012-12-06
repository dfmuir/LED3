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


char data;


int main (void)
{
    
    
    MCUCSR = (1<<JTD); // Enable full use of port C by disabling JTAG debugging
    MCUCSR = (1<<JTD); // TODO possibly remove
    
    
    DDRD = 0xFF;           /* make the LED pin an output */
    PORTD = 0xFF;
    DDRC = 0xFF;
    PORTC = 0xFF;

    
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