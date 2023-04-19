#ifndef AUDIO_H
#define AUDIO_H

#include <stdint.h>
#include "hardware/audio/midi.h"
#include "midiplay.h"

// The number of simultaneous voices to support.
#define VOICES 15

// An array of "voices".  Each voice can be used to play a different note.
// Each voice can be associated with a channel (explained later).
// Each voice has a step size and an offset into the wave table.
//struct {
//    uint8_t in_use;
//    uint8_t note;
//    uint8_t chan;
//    uint8_t volume;
//    int     step;
//    int     offset;
//} voice[VOICES];
typedef struct voice_struct{
    uint8_t in_use;
    uint8_t note;
    uint8_t chan;
    uint8_t volume;
    int     step;
    int     offset;
} voice_struct;

extern voice_struct voice[];
extern MIDI_Player *mp;

void note_off(int time, int chan, int key, int velo);
void note_on(int time, int chan, int key, int velo);
void set_tempo(int time, int value, const MIDI_Header *hdr);
void pitch_wheel_change(int time, int chan, int value);


#endif
