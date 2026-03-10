#ifndef DRIVER_MUSIC_H
#define DRIVER_MUSIC_H

#include <stdint.h>

/*
Driver for controlling the speaker like a musical instrument.
You can define a melody and play it in the background.
*/

typedef enum {
    NOTE_PAUSE = 0, 
    // Octave 4
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
    // Octave 5
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
    NOTE_B5  = 988,
    // Octave 6
    NOTE_C6 = 1047
} note_pitch_t;

typedef enum{
	WHOLE=16,	// 1/1
	HALF=8,		// 1/2
    QUARTER=4,	// 1/4
	EIGHTH=2,	// 1/8
	SIXTEENTH=1,// 1/16
    // end of melody marker
    END_OF_MELODY = 0
} note_value_t;

typedef struct {
	note_pitch_t pitch;
	note_value_t value;
} note_t;


void MUSIC_set_bpm(uint8_t bpm);    // Default BPM is 120 if this function is not called.
uint16_t MUSIC_note_value_to_ms(note_value_t value);

void MUSIC_play_note(note_pitch_t pitch, note_value_t note_value);
void MUSIC_play_melody(const note_t* melody);
void MUSIC_stop_melody(void);

uint8_t MUSIC_is_playing(void);

void MUSIC_system_tick(void);

#endif