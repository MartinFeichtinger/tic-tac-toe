#ifndef SPEAKER_H
#define SPEAKER_H

#include <stdint.h>

typedef enum {
    NOTE_PAUSE = 0,
    // Oktave 4
    NOTE_C4  = 262,
    NOTE_CS4 = 277,
    NOTE_D4  = 294,
    NOTE_DS4 = 311,
    NOTE_E4  = 330,
    NOTE_F4  = 349,
    NOTE_FS4 = 370,
    NOTE_G4  = 392,
    NOTE_GS4 = 415,
    NOTE_A4  = 440,
    NOTE_AS4 = 466,
    NOTE_B4  = 494,
    // Oktave 5
    NOTE_C5  = 523,
    NOTE_CS5 = 554,
    NOTE_D5  = 587,
    NOTE_DS5 = 622,
    NOTE_E5  = 659,
    NOTE_F5  = 698,
    NOTE_FS5 = 740,
    NOTE_G5  = 784,
    NOTE_GS5 = 831,
    NOTE_A5  = 880,
    NOTE_AS5 = 932,
    NOTE_B5  = 988
} musical_note_t;

void SPEAKER_init(void);
void SPEAKER_play_sound(musical_note_t note, uint16_t duration_ms);
void SPEAKER_system_tick(void);		// updates the duration coundown and turns off the sound

#endif