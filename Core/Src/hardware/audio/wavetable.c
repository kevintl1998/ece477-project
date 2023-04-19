#include <math.h>
#include "hardware/audio/midiplay.h"

short int wavetable[WAVETABLE_SIZE];

// sine wave
void init_wavetable_sine(void) {
    int x;
    for(x=0; x<WAVETABLE_SIZE; x++) {
        wavetable[x] = 32767 * sin(2 * M_PI * x / WAVETABLE_SIZE);
    }
}

// sawtooth wave
void init_wavetable_sawtooth(void) {
    int x;
    for(x=0; x<WAVETABLE_SIZE; x++)
        wavetable[x] = 32767.0 * (x - WAVETABLE_SIZE/2) / (1.0*WAVETABLE_SIZE);
}

// square wave
void init_wavetable_square(void) {
    int x;
    for(x=0; x<WAVETABLE_SIZE; x++)
        if (x < WAVETABLE_SIZE/2)
            wavetable[x] = -32767;
        else
            wavetable[x] = 32767;
}

// 1/2 amplitude sine wave added to 1/2 amplitude sawtooth wave
void init_wavetable_hybrid(void) {
    int x;
    for(x=0; x<WAVETABLE_SIZE; x++)
        wavetable[x] = 16383 * sin(2 * M_PI * x / WAVETABLE_SIZE) + 16383.0 * (x - WAVETABLE_SIZE/2) / (1.0*WAVETABLE_SIZE);
}

// 3/4 amplitude sine wave added to 1/4 amplitude sawtooth wave
void init_wavetable_hybrid2(void) {
    int x;
    for(x=0; x<WAVETABLE_SIZE; x++)
        wavetable[x] = 3*8191 * sin(2 * M_PI * x / WAVETABLE_SIZE) + 8191.0 * (x - WAVETABLE_SIZE/2) / (1.0*WAVETABLE_SIZE);
}
