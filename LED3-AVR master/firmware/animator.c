#include "state.h"


int go = 0;
int repeat_count, delay_count;

int state_count, total_states;

struct state *animation_sequence[500];

struct state *current_state;

void (*f)();

int j = 0;

void next_state() {
    if(go) {
        if(repeat_count < current_state->num_repeat) {
            if(delay_count == 0) {
                current_state->function(repeat_count);
            }
            
            delay_count = (delay_count+1)%current_state->delay;
            if(delay_count == 0) {
                repeat_count++;
            }

        }
        else {
            repeat_count = 0;
            delay_count = 0;
            if(state_count < total_states) {
                current_state = animation_sequence[state_count];
                state_count++;
            }
            else {
                go = 0;
            }
            
        }
        
    }
}

void perform_animation(int num_states) {
    clear_buffer();

    current_state = animation_sequence[0];
    total_states = num_states;
    state_count = 0;
    repeat_count = 0;
    delay_count = 0;
    go = 1;
}

