#ifndef DRIVER_PLAY_BUTTONS_H
#define DRIVER_PLAY_BUTTONS_H

#define DEBOUNCE_TICKS		10		// ms
#define LONG_PRESS_TICKS	1000	// ms

typedef enum{
	SHORT,
	LONG
} button_press_type_t;

void PLAY_BUTTONS_init(void);

typedef void (*PLAY_BUTTONS_next_button_callback_t)(button_press_type_t press_type);
typedef void (*PLAY_BUTTONS_ok_button_callback_t)(button_press_type_t press_type);
void PLAY_BUTTONS_set_next_button_callback(PLAY_BUTTONS_next_button_callback_t callback);
void PLAY_BUTTONS_set_ok_button_callback(PLAY_BUTTONS_ok_button_callback_t callback);

void PLAY_BUTTONS_system_tick(void);

#endif