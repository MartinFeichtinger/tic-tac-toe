#ifndef DRIVER_MUSIC_H
#define DRIVER_MUSIC_H

#include <stdint.h>

/*
This is a driver to use the speaker like an musician 
you can define an melody and let it play in the background
*/

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
    NOTE_B5  = 988,
    // end of melody marker 
    END_OF_MELODY = 0
} musical_note_t;

typedef enum{
	LEN_WHOLE=16,	// 1/1
	LEN_HALF=8,		// 1/2
	LEN_QUARTER=4,	// 1/4
	LEN_EIGHTH=2,	// 1/8
	LEN_SIXTEENTH=1	// 1/16
} note_length_t;

typedef struct {
	musical_note_t note;
	note_length_t duration;
} note_t;

void MUSIC_set_bpm(uint8_t music_bpm);    // if this function isn't called, the default bpm value is 120
void MUSIC_play_melody(const note_t* melody);
void MUSIC_system_tick(void);
uint8_t MUSIC_is_playing(void);

#endif