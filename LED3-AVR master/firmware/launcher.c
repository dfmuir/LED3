#include "animations.c"



void launch_diagonal() {
    struct state *s1 = malloc(sizeof(struct state));
    s1->num_repeat = 3*8;
    s1->delay = 5;
    s1->function = diagonal;
    animation_sequence[0] = s1;
    
    
    struct state *s2 = malloc(sizeof(struct state));
    s2->num_repeat = 3*8;
    s2->delay = 20;
    s2->function = face;
    animation_sequence[1] = s2;
    
    
    perform_animation(2);
}

void launch_led3_blue() {
    struct state *s1 = malloc(sizeof(struct state));
    s1->num_repeat = 96;
    s1->delay = 2;
    s1->function = led3_blue;
    
    animation_sequence[0] = s1;
    perform_animation(1);
}

void launch_led3_front_to_back() {
    
    struct state *s1 = malloc(sizeof(struct state));
    s1->num_repeat = 96;
    s1->delay = 2;
    s1->function = led3;
    
    animation_sequence[0] = s1;
    perform_animation(1);


}

void launch_led3_rotate() {
    
    struct state *s1 = malloc(sizeof(struct state));
    s1->num_repeat = 500;
    s1->delay = 15;
    s1->function = led3_rotate;
    
    animation_sequence[0] = s1;
    perform_animation(1);
    
    
}

void launch_grow_cube() {
    struct state *s1 = malloc(sizeof(struct state));
    s1->num_repeat = 640;
    s1->delay = 4;
    s1->function = grow_cube;
    
    animation_sequence[0] = s1;
    perform_animation(1);

}

void launch_rainMaker() {
    struct state *s1 = malloc(sizeof(struct state));
    s1->num_repeat = 1000;
    s1->delay = 2;
    s1->function = rainMaker;
    
    animation_sequence[0] = s1;
    perform_animation(1);

}

void launch_rainbowRainMaker() {
    struct state *s1 = malloc(sizeof(struct state));
    s1->num_repeat = 1000;
    s1->delay = 2;
    s1->function = rainbowRainMaker;
    
    animation_sequence[0] = s1;
    perform_animation(1);

}

void launch_danceAlien() {
    struct state *s1 = malloc(sizeof(struct state));
    s1->num_repeat = 1000;
    s1->delay = 20;
    s1->function = danceAlien;
    
    animation_sequence[0] = s1;
    perform_animation(1);

}

// Pictures

void launch_four_cubes() {
    four_cubes();
        update();
}

void launch_Aplus() {
    letter_Aplus( color_blue );
        update();
}

void launch_flag() {
    flag();
    update();
}

void launch_bluebox() {
    bluebox();
    update();
}