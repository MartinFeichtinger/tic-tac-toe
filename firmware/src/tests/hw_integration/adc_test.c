/*
this is unfotunatly just a test for the program and not the hardware.
the problem is that we don't have any serial output. maybe i will use display or the speaker later...
*/

#include "config.h"
#include "hal_adc.h"
#include "hal_gpio.h"

int main(void)
{
	GPIO_INIT_INPUT(PLAY_BUTTONS);
	GPIO_INIT_INPUT(MODE_SWITCHES);
	
	ADC_init();
	uint16_t adc_value=0;

	while(1)
	{
		adc_value=ADC_READ(PLAY_BUTTONS);
	}
}