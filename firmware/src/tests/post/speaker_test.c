#include "driver_speaker.h"
#include <stdint.h>
#include "hal_time.h"

void system_ticks_callback_handler(void);

int main(void)
{
	SPEAKER_init();
	TIME_init();
	TIME_set_system_ticks_callback(system_ticks_callback_handler);

	for(uint16_t freq=100; freq<=1500; freq+=100)
	{
		SPEAKER_play_sound(freq, 300);
		TIME_delay_ms(500);
	}
}


void system_ticks_callback_handler(void)
{
	SPEAKER_system_tick();
}