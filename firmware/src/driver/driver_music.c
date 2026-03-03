#include "driver_music.h"
#include <stdint.h>
#include <stddef.h>
#include "driver_speaker.h"

static const note_t* current_melody=NULL;
static uint16_t current_note_intex=0;
static uint16_t note_timer=0;

static uint8_t bpm = 120;

void MUSIC_set_bpm(uint8_t music_bpm)
{
	bpm=music_bpm;
}


static uint16_t note_duration_to_ms(note_length_t length)
{
	// 1min = 60000ms
	// 1bpm => on 1/4 per minute for a 4/4 rhythm
	// => duration for 1/4 note = (60.000ms/min)/bpm = something with ms
	// our base for note_length_t is 1/16 => base = (duration for 1/4 note) / 4
	uint16_t base_ms=60000/bpm/4;

	return (uint16_t)length*base_ms;
}


void MUSIC_play_melody(const note_t* melody)
{
	current_melody=melody;
	current_note_intex=0;
	note_timer=1;			// start melody at next system tick
}


void MUSIC_system_tick(void)
{
	if(current_melody == NULL) return;

	if(note_timer > 0)
	{
		note_timer--;
	}

	if(note_timer == 0)
	{
		note_t next_note=current_melody[current_note_intex];
		
		if(next_note.note == END_OF_MELODY)
		{
			current_melody=NULL;
		}
		else
		{
			uint16_t duration_ms=note_duration_to_ms(next_note.duration);

			SPEAKER_play_sound(next_note.note, duration_ms-20);

			note_timer=duration_ms;
			current_note_intex++;
		}
	}
}


uint8_t MUSIC_is_playing(void)
{
	if(current_melody != NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
