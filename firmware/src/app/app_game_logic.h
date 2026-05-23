#ifndef APP_GAME_LOGIC_H
#define	APP_GAME_LOGIC_H

#include <stdint.h>
#include "driver_play_buttons.h"

#define BOARD_SIZE	3

// main game logic function
void GAME_LOGIC_run_game(void);

// button input handler
void GAME_LOGIC_next_button_callback_handler(button_press_type_t press_type);
void GAME_LOGIC_ok_button_callback_handler(button_press_type_t press_type);


#endif