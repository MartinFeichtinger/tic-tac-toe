#ifndef DRIVER_LED_DISPLAY_H
#define DRIVER_LED_DISPLAY_H

typedef enum
{
	LED_OFF = 0,
	LED_ON_GREEN = 1,
	LED_ON_RED = 2
} led_state_t;

void LED_DISPLAY_init(void);
void LED_DISPLAY_update_buffer(led_state_t led_display_buffer[3][3]);

#endif