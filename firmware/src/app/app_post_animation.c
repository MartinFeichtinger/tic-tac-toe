#include "app_post_animation.h"

#include "hal_time.h"

#include "driver_led_display.h"
#include "driver_music.h"

#include <stdint.h>


static const note_t post_melody[] = {
	{NOTE_C4, EIGHTH},
	{NOTE_D4, EIGHTH}, 
	{NOTE_E4, EIGHTH}, 
	{NOTE_F4, EIGHTH}, 
	{NOTE_G4, EIGHTH}, 
	{NOTE_A4, EIGHTH},
	{NOTE_B4, EIGHTH},
    {NOTE_C5, QUARTER},

	{NOTE_C5, EIGHTH},
	{NOTE_D5, EIGHTH}, 
	{NOTE_E5, EIGHTH}, 
	{NOTE_F5, EIGHTH}, 
	{NOTE_G5, EIGHTH}, 
	{NOTE_A5, EIGHTH},
	{NOTE_B5, EIGHTH},
    {NOTE_C6, QUARTER},
	{NOTE_PAUSE, END_OF_MELODY}
};

static void clear_game_board(led_state_t game_board[3][3]);

void post_animation(void)
{
	led_state_t game_board[3][3];
	clear_game_board(game_board);

	MUSIC_play_melody(post_melody);

	// turn all leds green
	for(uint8_t row=0; row<3; row++)
	{
		for(uint8_t col=0; col<3; col++)
		{
			game_board[col][row]=LED_ON_GREEN;
			LED_DISPLAY_update_buffer(game_board);
			TIME_delay_ms(MUSIC_note_value_to_ms(EIGHTH));
		}
	}
	// turn all leds red
	for(uint8_t row=0; row<3; row++)
	{
		for(uint8_t col=0; col<3; col++)
		{
			game_board[col][row]=LED_ON_RED;
			LED_DISPLAY_update_buffer(game_board);
			TIME_delay_ms(MUSIC_note_value_to_ms(EIGHTH));
		}
	}
	// turn all led off
	clear_game_board(game_board);
	LED_DISPLAY_update_buffer(game_board);
}


static void clear_game_board(led_state_t game_board[3][3])
{
	for(uint8_t row=0; row<3; row++)
	{
		for(uint8_t col=0; col<3; col++)
		{
			game_board[col][row]=LED_OFF;
		}
	}
}