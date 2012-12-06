//#include "animator.c"

int data_transfer = 0;
int spi_load_layer = 0;
int spi_load_ff = 0;


ISR (TIMER0_OVF_vect) {
    next_state();
}

ISR (SPI_STC_vect) {
    go = 0;
    int byte_code = SPDR;
    
    if(data_transfer) {
        buffer[spi_load_layer][spi_load_ff] = SPDR;
        
        spi_load_ff++;
        
        if(spi_load_ff == 24) {
            spi_load_ff = 0;
            spi_load_layer++;
            if(spi_load_layer == 8) {
                spi_load_layer = 0;
                update();
                data_transfer = 0;
            }
        }
        
    }
    else {
        switch (byte_code) {
                // Still frames
                
            case 100:
                launch_rainbowRainMaker();
                break;
            case 101:
                launch_rainMaker();
                break;
            case 102:
                launch_diagonal();
                break;
            case 103:
                launch_grow_cube();
                break;
            case 104:
                launch_led3_front_to_back();
                break;
            case 105:
                launch_led3_rotate();
                break;
            case 106:
                launch_led3_blue();
                break;
            case 107:
                launch_danceAlien();
                break;
            
                
            case 200:
                four_cubes();
                break;
            case 201:
                launch_flag();
                break;
            case 202:
                launch_Aplus();
                break;
            case 203:
                launch_bluebox();
                break;

            case 255:
                data_transfer = 1;
                break;
                
            default:
                break;
                
        }
    }
}