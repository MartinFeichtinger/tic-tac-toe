#include "driver_mode_switches.h"
#include "config.h"
#include "hal_gpio.h"
#include "hal_adc.h"


void MODE_SWITCHES_init(void)
{
	GPIO_INIT_INPUT(MODE_SWITCHES);
	ADC_init();
}


mode_t MODE_SWITCHES_get_mode(void)
{
	uint16_t adc_value = ADC_READ(MODE_SWITCHES);

	// analog switch values
	// MODE_3	5.00V
	// MODE_2	3.37V
	// MODE_1	2.74V
	// MODE_0	2.17V
	
	const uint16_t adc_faktor = 205;	// 1024 values / 5V		=> (voltage)*adc_faktor can be compared to the adc_value

	if(adc_value >= 4.5*adc_faktor)
	{
		return MODE_3;
	}
	else if(adc_value >= 3*adc_faktor)
	{
		return MODE_2;
	}
	else if(adc_value >= 2.4*adc_faktor)
	{
		return MODE_1;
	}
	else
	{
		return MODE_0;
	}
	
}