#include "driver_led_display.h"
#include "hal_time.h"
#include "config.h"
#include <util/delay.h>

void clear_game_board(led_state_t game_board[3][3]);

int main(void)
{
	TIMER_init_timer_0();
	LED_DISPLAY_init();
	led_state_t game_board[3][3];
	clear_game_board(game_board);


	// turn all leds green
	for(uint8_t row=0; row<3; row++)
	{
		for(uint8_t col=0; col<3; col++)
		{
			game_board[col][row]=LED_ON_GREEN;
			LED_DISPLAY_update_buffer(game_board);
			_delay_ms(300);
		}
	}
	// turn all leds red
	for(uint8_t row=0; row<3; row++)
	{
		for(uint8_t col=0; col<3; col++)
		{
			game_board[col][row]=LED_ON_RED;
			LED_DISPLAY_update_buffer(game_board);
			_delay_ms(300);
		}
	}
	// turn all leds off
	for(uint8_t row=0; row<3; row++)
	{
		for(uint8_t col=0; col<3; col++)
		{
			game_board[col][row]=LED_OFF;
			LED_DISPLAY_update_buffer(game_board);
			_delay_ms(300);
		}
	}
}

void clear_game_board(led_state_t game_board[3][3])
{
	for(uint8_t row=0; row<3; row++)
	{
		for(uint8_t col=0; col<3; col++)
		{
			game_board[col][row]=LED_OFF;
		}
	}
}