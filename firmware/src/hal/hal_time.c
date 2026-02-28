#include "hal_time.h"

static volatile uint32_t system_millis=0;

ISR(TIMER0_COMPA_vect)
{
	system_millis++;
}

uint32_t TIME_get_millis()
{
	uint32_t return_value;
	cli();
	return_value=system_millis;
	sei();
	return return_value;
}