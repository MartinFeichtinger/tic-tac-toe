#include "driver_music.h"
#include "driver_speaker.h"
#include <stdint.h>
#include "hal_time.h"

static const note_t alle_meine_entchen[] = {
    {NOTE_C5, EIGHTH}, {NOTE_D5, EIGHTH}, {NOTE_E5, EIGHTH}, {NOTE_F5, EIGHTH}, {NOTE_G5, QUARTER}, {NOTE_G5, QUARTER},
    {NOTE_A5, EIGHTH}, {NOTE_A5, EIGHTH}, {NOTE_A5, EIGHTH}, {NOTE_A5, EIGHTH}, {NOTE_G5, HALF},
    {NOTE_A5, EIGHTH}, {NOTE_A5, EIGHTH}, {NOTE_A5, EIGHTH}, {NOTE_A5, EIGHTH}, {NOTE_G5, HALF},
    {NOTE_F5, EIGHTH}, {NOTE_F5, EIGHTH}, {NOTE_F5, EIGHTH}, {NOTE_F5, EIGHTH}, {NOTE_E5, QUARTER}, {NOTE_E5, QUARTER},
    {NOTE_D5, EIGHTH}, {NOTE_D5, EIGHTH}, {NOTE_D5, EIGHTH}, {NOTE_D5, EIGHTH}, {NOTE_C5, HALF},
	{NOTE_PAUSE, END_OF_MELODY}
};


void system_ticks_callback_handler(void);

int main(void)
{
	SPEAKER_init();
	TIME_init();
	TIME_set_system_ticks_callback(system_ticks_callback_handler);
    
    MUSIC_play_note(NOTE_C5, WHOLE);

    while(MUSIC_is_playing());

    MUSIC_play_melody(alle_meine_entchen);

    while(1);
}

void system_ticks_callback_handler(void)
{
	SPEAKER_system_tick();
    MUSIC_system_tick();
}