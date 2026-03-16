#include "driver_play_buttons.h"
#include <stddef.h>
#include <stdbool.h>
#include "config.h"
#include "hal_gpio.h"
#include "hal_adc.h"


static bool next_button_pressed=false;
static bool ok_button_pressed=false;

static uint16_t next_button_ticks_counter=0;
static uint16_t ok_button_ticks_counter=0;


void PLAY_BUTTONS_init(void)
{
	GPIO_INIT_INPUT(PLAY_BUTTONS);
	ADC_init();
}


static PLAY_BUTTONS_next_button_callback_t next_button_callback = NULL; 
void PLAY_BUTTONS_set_next_button_callback(PLAY_BUTTONS_next_button_callback_t callback)
{
	next_button_callback=callback;
}


static PLAY_BUTTONS_ok_button_callback_t ok_button_callback = NULL; 
void PLAY_BUTTONS_set_ok_button_callback(PLAY_BUTTONS_ok_button_callback_t callback)
{
	ok_button_callback = callback;
}

void PLAY_BUTTONS_system_tick(void)
{
	uint16_t adc_value = ADC_READ(PLAY_BUTTONS);

	// analog button values
	// BOTH			5.00V
	// BUTTON_OK	3.37V
	// BUTTON_NEXT	2.74V
	// NONE			2.17V
	
	const uint16_t adc_faktor = 205;	// 1024 values / 5V		=> (voltage)*adc_faktor can be compared to the adc_value

	if(adc_value >= 4.5*adc_faktor)
	{
		next_button_pressed=true;
		ok_button_pressed=true;
	}
	else if(adc_value >= 3*adc_faktor)
	{
		next_button_pressed=false;
		ok_button_pressed=true;
	}
	else if(adc_value >= 2.4*adc_faktor)
	{
		next_button_pressed=true;
		ok_button_pressed=false;
	}
	else
	{
		next_button_pressed=false;
		ok_button_pressed=false;
	}

	if(next_button_pressed)
	{
		if(next_button_ticks_counter < 0xFFFF) next_button_ticks_counter++;
	}
	else // next_button is released
	{
		if(next_button_ticks_counter >= DEBOUNCE_TICKS)
		{
			if(next_button_callback != NULL) next_button_callback();
		}

		next_button_ticks_counter=0;
	}

	if(ok_button_pressed)
	{
		if(ok_button_ticks_counter < 0xFFFF) ok_button_ticks_counter++;
	}
	else // ok_button is released
	{
		if(ok_button_ticks_counter >= DEBOUNCE_TICKS)
		{
			if(ok_button_callback != NULL) ok_button_callback();
		}

		ok_button_ticks_counter=0;
	}
}
