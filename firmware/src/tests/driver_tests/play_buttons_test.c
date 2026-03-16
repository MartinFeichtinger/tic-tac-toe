#include "driver_play_buttons.h"
#include "driver_led_display.h"
#include "hal_time.h"

#define BOARD_SIZE	3

struct Boardpositon
{
	uint8_t x;
	uint8_t y;
} pos;

led_state_t game_board[3][3];


void system_ticks_callback_handler(void);
void next_button_callback_handler(void);
void ok_button_callback_handler(void);

static void clear_game_board(led_state_t game_board[3][3]);

int main(void)
{
	TIME_init();
	TIME_set_system_ticks_callback(system_ticks_callback_handler);
	
	PLAY_BUTTONS_init();
	PLAY_BUTTONS_set_next_button_callback(next_button_callback_handler);
	PLAY_BUTTONS_set_ok_button_callback(ok_button_callback_handler);
	
	LED_DISPLAY_init();

	clear_game_board(game_board);
	pos.x=0; pos.y=0;

	while(1)
	{
		LED_DISPLAY_update_buffer(game_board);
		TIME_delay_ms(100);
	}
}


void system_ticks_callback_handler(void)
{
	PLAY_BUTTONS_system_tick();
	LED_DISPLAY_system_tick();
}


void next_button_callback_handler(void)
{
	if(pos.x+1 < BOARD_SIZE)
	{
		pos.x++;
	}
	else if(pos.y+1 < BOARD_SIZE)
	{
		pos.y++;
		pos.x=0;
	}
	else
	{
		pos.x=0;
		pos.y=0;
	}
}


void ok_button_callback_handler(void)
{
	if(game_board[pos.x][pos.y] == LED_OFF)
	{
		game_board[pos.x][pos.y]=LED_ON_GREEN;
	}
	else if(game_board[pos.x][pos.y] == LED_ON_GREEN)
	{
		game_board[pos.x][pos.y]=LED_ON_RED;
	}
	else // game_board[pos.x][pos.y] == LED_ON_RED
	{
		game_board[pos.x][pos.y]=LED_OFF;
	}
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