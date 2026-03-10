#include "driver_music.h"
#include <stdint.h>
#include <stddef.h>
#include "driver_speaker.h"

static const note_t* current_melody=NULL;
static uint16_t current_note_index=0;
static uint16_t tick_countdown=0;

static uint8_t music_bpm = 120;

void MUSIC_set_bpm(uint8_t bpm)
{
	music_bpm=bpm;
}


uint16_t MUSIC_note_value_to_ms(note_value_t value)
{
	// 1min = 60000ms
	// 1bpm => on 1/4 per minute for a 4/4 rhythm
	// => duration for 1/4 note = (60.000ms/min)/bpm = something with ms
	// our base for note_length_t is 1/16 => base = (duration for 1/4 note) / 4
	uint16_t base_ms=60000/music_bpm/4;

	return (uint16_t)value*base_ms;
}


void MUSIC_play_note(note_pitch_t pitch, note_value_t value)
{
	uint16_t ms=MUSIC_note_value_to_ms(value);

	SPEAKER_play_sound(pitch, ms-20);

	tick_countdown=ms;
}


void MUSIC_play_melody(const note_t* melody)
{
	current_melody=melody;
	current_note_index=0;
	tick_countdown=1;			// start melody at next system tick
}

void MUSIC_stop_melody(void)
{
	current_melody=NULL;
}


uint8_t MUSIC_is_playing(void)
{
	if(tick_countdown > 0 || current_melody != NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


void MUSIC_system_tick(void)
{
	if(tick_countdown > 0)
	{
		tick_countdown--;
	}

	if(current_melody == NULL) return;

	if(tick_countdown == 0)
	{
		note_t next_note=current_melody[current_note_index];
		
		if(next_note.value == END_OF_MELODY)
		{
			current_melody=NULL;
		}
		else
		{
			MUSIC_play_note(next_note.pitch, next_note.value);
			current_note_index++;
		}
	}
}