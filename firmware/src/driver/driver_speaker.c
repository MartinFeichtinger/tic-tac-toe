#include "driver_speaker.h"
#include <stdint.h>
#include "hal_gpio.h"
#include "hal_timer.h"
#include "hal_time.h"

static volatile uint16_t duration_ms_countdown = 0;


void SPEAKER_init(void)
{
	GPIO_INIT_OUTPUT(SPEAKER);
	TIMER_init_timer_1();
}


void SPEAKER_play_sound(uint16_t frequncy, uint16_t duration_ms)
{
	TIMER_set_timer_1_frequency(frequncy);
	duration_ms_countdown = duration_ms;
}


void SPEAKER_system_tick(void)
{
	if(duration_ms_countdown > 0)
	{
		duration_ms_countdown--;
		if(duration_ms_countdown == 0)
		{
			TIMER_set_timer_1_frequency(0);		// stop timer 1
		}
	}
}