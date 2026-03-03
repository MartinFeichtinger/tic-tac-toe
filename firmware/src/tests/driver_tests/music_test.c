#include "driver_music.h"
#include "driver_speaker.h"
#include <stdint.h>
#include "hal_time.h"

static const note_t alle_meine_entchen[] = {
    {NOTE_C5, LEN_EIGHTH}, {NOTE_D5, LEN_EIGHTH}, {NOTE_E5, LEN_EIGHTH}, {NOTE_F5, LEN_EIGHTH}, {NOTE_G5, LEN_QUARTER}, {NOTE_G5, LEN_QUARTER},
    {NOTE_A5, LEN_EIGHTH}, {NOTE_A5, LEN_EIGHTH}, {NOTE_A5, LEN_EIGHTH}, {NOTE_A5, LEN_EIGHTH}, {NOTE_G5, LEN_HALF},
    {NOTE_A5, LEN_EIGHTH}, {NOTE_A5, LEN_EIGHTH}, {NOTE_A5, LEN_EIGHTH}, {NOTE_A5, LEN_EIGHTH}, {NOTE_G5, LEN_HALF},
    {NOTE_F5, LEN_EIGHTH}, {NOTE_F5, LEN_EIGHTH}, {NOTE_F5, LEN_EIGHTH}, {NOTE_F5, LEN_EIGHTH}, {NOTE_E5, LEN_QUARTER}, {NOTE_E5, LEN_QUARTER},
    {NOTE_D5, LEN_EIGHTH}, {NOTE_D5, LEN_EIGHTH}, {NOTE_D5, LEN_EIGHTH}, {NOTE_D5, LEN_EIGHTH}, {NOTE_C5, LEN_HALF},
	{END_OF_MELODY, 0}
};


void system_ticks_callback_handler(void);

int main(void)
{
	SPEAKER_init();
	TIME_init();
	TIME_set_system_ticks_callback(system_ticks_callback_handler);
    
    MUSIC_play_melody(alle_meine_entchen);

    while(1);
}

void system_ticks_callback_handler(void)
{
	SPEAKER_system_tick();
    MUSIC_system_tick();
}