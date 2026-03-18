#include "hal_time.h"

#include "driver_led_display.h"
#include "driver_speaker.h"
#include "driver_music.h"
#include "driver_mode_switches.h"
#include "driver_play_buttons.h"

#include "app_post_animation.h"

#include <stdint.h>

void system_ticks_callback_handler(void);

int main(void)
{
	// many driver inits
	TIME_init();
	TIME_set_system_ticks_callback(system_ticks_callback_handler);

	LED_DISPLAY_init();
	SPEAKER_init();
	MODE_SWITCHES_init();
	PLAY_BUTTONS_init();

	// run post animation
	post_animation();

	// run game application


	while(1);
}


void system_ticks_callback_handler(void)
{
	LED_DISPLAY_system_tick();
	SPEAKER_system_tick();
    MUSIC_system_tick();
	PLAY_BUTTONS_system_tick();
}