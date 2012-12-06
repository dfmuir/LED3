#define DD_MOSI     PINB3
#define DD_MISO     PINB4

#define DD_SCK      PINB5
#define DDR_SPI     PORTB


void init_ports() {
    //MCUCSR = (1<<JTD); // Enable full use of port C by disabling JTAG debugging
    //MCUCSR = (1<<JTD); // TODO possibly remove
    
    //MCUCSR = 0;
    
    //DDRA = 0xFF; // Make PORTA outputs
    //DDRB = 0xFF; // Make PORTB outputs
    //DDRC = 0xFF; // Make PORTC outputs
    
    PORTB = 0x00;
}



void init_spi() {
    /* Set MOSI and SCK output, all others input */
    DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK);
    /* Enable SPI, Master, set clock rate fck/16 */
    SPCR = (1<<SPE)|(1<<CPOL)|(1<<CPHA)|(1<<MSTR)|(1<<SPR0);      // SPI enable / Clock polarity 1 / SPI interrupts enable

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