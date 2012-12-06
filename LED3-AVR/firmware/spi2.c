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

void init_ports() {
    MCUCSR = (1<<JTD); // Enable full use of port C by disabling JTAG debugging
    MCUCSR = (1<<JTD); // TODO possibly remove
    
    DDRA = 0xFF; // Make PORTA outputs
    DDRB = 0xFF; // Make PORTB outputs
    DDRC = 0xFF; // Make PORTC outputs

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


int main (void) {
    
    init_ports();
    init_spi();

    int blue[] = { 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0, 0x00, 0x00, 0, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00};

    
    while(1) {

        write(red, 24, i);

        i = (i + 1) % 8;
        
    }
}



ISR (SPI_STC_vect)                         // Interrupt on Int0 vector

{
    
    data = SPDR;
    PORTC = data;

    PORTC = SPDR;

    
    
}