#include <avr/io.h>

char layer_select[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

char current_cube[8][24];
char buffer[8][24];


int layer = 0;

void update() {
    memcpy(current_cube, buffer, 192);
}

void fire_clock (void) {
    
    PORTB = 1;
    PORTB = 0;
    //_delay_ms(0.01);
}

void write(char *d, int layer_select_index) {
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

void start_cube() {
    while(1) {
        write(current_cube[layer], layer);
        layer = (layer+1)%8;
    }
}