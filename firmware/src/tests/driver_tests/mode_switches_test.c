#include "driver_mode_switches.h"

#include <stdint.h>
#include "hal_time.h"
#include "driver_led_display.h"


void system_ticks_callback_handler(void);
static void clear_game_board(led_state_t game_board[3][3]);


int main(void)
{
	MODE_SWITCHES_init();
	
	LED_DISPLAY_init();
	TIME_init();
	TIME_set_system_ticks_callback(system_ticks_callback_handler);

	led_state_t game_board[3][3];
	clear_game_board(game_board);

	while(1)
	{
		mode_t mode = MODE_SWITCHES_get_mode();
		switch(mode)
		{
			case MODE_0: game_board[0][0]=LED_ON_GREEN; break;
			case MODE_1: game_board[1][0]=LED_ON_GREEN; break;
			case MODE_2: game_board[2][0]=LED_ON_GREEN; break;
			case MODE_3: game_board[0][1]=LED_ON_GREEN; break;
		}

		LED_DISPLAY_update_buffer(game_board);
		TIME_delay_ms(500);
		clear_game_board(game_board);
	}
}


void system_ticks_callback_handler(void)
{
	LED_DISPLAY_system_tick();
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