#define DD_MOSI     PINB3
#define DD_MISO     PINB4

#define DD_SCK      PINB5
#define DDR_SPI     PORTB


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
    
    SPCR = (1<<SPE)|(1<<SPIE);      // SPI enable / Clock polarity 1 / SPI interrupts enable
    
    sei();
}

void init_animation_timer() {
    // Prescaler = FCPU/1024
    TCCR0|=(1<<CS02)|(1<<CS01);
    
    //Enable Overflow Interrupt Enable
    TIMSK|=(1<<TOIE0);
    
    //Initialize Counter
    TCNT0=0;

    
    //Enable Global Interrupts
    sei();
}