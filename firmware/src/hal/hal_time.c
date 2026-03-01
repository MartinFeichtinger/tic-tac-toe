#include "hal_time.h"
#include <stddef.h>


static volatile uint32_t system_millis=0;

uint32_t TIME_get_millis()
{
	uint32_t return_value;
	cli();
	return_value=system_millis;
	sei();
	return return_value;
}


static TIME_system_ticks_callback_t system_ticks_callback = NULL; 

void TIME_set_system_ticks_callback(TIME_system_ticks_callback_t callback)
{
	system_ticks_callback = callback;
}


ISR(TIMER0_COMPA_vect)
{
	system_millis++;
	if(system_ticks_callback != NULL) // prevent attiny form crashing when callback isn't confiugrated yet
	{
		system_ticks_callback();
	}
}