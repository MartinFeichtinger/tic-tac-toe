#include "hal_adc.h"
#include "config.h"

void ADC_init(void)
{
	// cofigurate ADC for analog pins BUTTONS and MODE
	ADCSRA|=(1<<ADEN);				// enable ADC
	ADCSRA|=(1<<ADPS2)|(1<<ADPS1);	// set ADC prescaler to 64 (8MHz/64=125kHz ... should be between 50Hz and 200Hz)
	DIDR0|=(1<<ADC6D)|(1<<ADC5D);	// disable digital buffer of the analog pins to reduce power consumption	
}

uint16_t _ADC_read(uint8_t pin, uint8_t port)
{
	if(!((port>>pin)&1))				// check if pin is an input
	{
		ADMUX=(pin-1);					// set mutiplexer at input pin
		ADCSRA|=(1<<ADSC);				// start conversation
		while(ADCSRA&(0x01<<ADSC)) {};	// wait untile the conversation is finished
	}
	
	return ADC;
}
