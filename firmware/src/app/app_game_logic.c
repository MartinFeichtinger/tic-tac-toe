#include "app_game_logic.h"

#include <stdint.h>
#include <stdbool.h>

#include "driver_mode_switches.h"
#include "driver_play_buttons.h"
#include "driver_led_display.h"
#include "driver_music.h"

#include "hal_time.h"


typedef enum
{
	NONE,
	PLAYER_1,
	PLAYER_2
} player_t;

typedef struct 
{
	uint8_t x;
	uint8_t y;
} position_t;

typedef struct
{
	player_t player;
	position_t pos;
} current_player_t;

typedef enum
{
	EMPTY,
	OCCUPIED,
	WINNING_STEAK	// marker for the victory animation
} field_status_t;

typedef struct 
{
	player_t owner;
	field_status_t status;
} game_field_t;


static void clear_game_board(game_field_t game_board[BOARD_SIZE][BOARD_SIZE]);
static void update_display(game_field_t game_board[BOARD_SIZE][BOARD_SIZE], current_player_t player);

void GAME_LOGIC_run_game(void)
{
	bool game_over=false;
	current_player_t current_player;
	game_field_t game_board[BOARD_SIZE][BOARD_SIZE];

	current_player.player=PLAYER_1;
	current_player.pos.x=1;
	current_player.pos.y=1;

	clear_game_board(game_board);

	while(!game_over)
	{
		TIME_delay_ms(100);		

		update_display(game_board, current_player);
	}
}


static void clear_game_board(game_field_t game_board[3][3])
{
	for(uint8_t row=0; row<3; row++)
	{
		for(uint8_t col=0; col<3; col++)
		{
			game_board[col][row].owner = NONE;
			game_board[col][row].status = EMPTY;
		}
	}
}


static void update_display(game_field_t game_board[BOARD_SIZE][BOARD_SIZE], current_player_t current_player)
{
	static uint32_t start_time=0;
	bool blinking_leds_on=false;

	if(start_time == 0) start_time=TIME_get_millis();
	else
	{
		if((TIME_get_millis()-start_time) % 1000 > 500)
		{
			blinking_leds_on=true;
		}
		else
		{
			blinking_leds_on=false;
		}
	}

	led_state_t display_buffer[BOARD_SIZE][BOARD_SIZE];

	for(uint8_t row=0; row<3; row++)
	{
		for(uint8_t col=0; col<3; col++)
		{
			if(game_board[col][row].status == OCCUPIED)
			{
				if(game_board[col][row].owner == PLAYER_1) display_buffer[col][row]=LED_ON_GREEN;
				else if(game_board[col][row].owner == PLAYER_2) display_buffer[col][row]=LED_ON_RED;
			}
			else if(game_board[col][row].status == EMPTY)
			{
				if(current_player.pos.x == col && current_player.pos.y == row && blinking_leds_on)
				{
					if(current_player.player == PLAYER_1) display_buffer[col][row]=LED_ON_GREEN;
					else if(current_player.player == PLAYER_2) display_buffer[col][row]=LED_ON_RED;
				}
				else
				{
					display_buffer[col][row]=LED_OFF;
				}	
			}
			else if(game_board[col][row].status == WINNING_STEAK)
			{
				if(blinking_leds_on)
				{
					if(game_board[col][row].owner == PLAYER_1) display_buffer[col][row]=LED_ON_GREEN;
					else if(game_board[col][row].owner == PLAYER_2) display_buffer[col][row]=LED_ON_RED;
				}
				else
				{
					display_buffer[col][row]=LED_OFF;
				}
			}
		}
	}

	LED_DISPLAY_update_buffer(display_buffer);
}