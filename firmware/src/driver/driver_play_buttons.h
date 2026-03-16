#ifndef DRIVER_PLAY_BUTTONS_H
#define DRIVER_PLAY_BUTTONS_H

#define DEBOUNCE_TICKS		10	// ms

void PLAY_BUTTONS_init(void);

typedef void (*PLAY_BUTTONS_next_button_callback_t)(void);
typedef void (*PLAY_BUTTONS_ok_button_callback_t)(void);
void PLAY_BUTTONS_set_next_button_callback(PLAY_BUTTONS_next_button_callback_t callback);
void PLAY_BUTTONS_set_ok_button_callback(PLAY_BUTTONS_ok_button_callback_t callback);

void PLAY_BUTTONS_system_tick(void);

#endif