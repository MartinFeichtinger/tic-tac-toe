#include "hal_timer.h"
#include <avr/interrupt.h>
#include <stdint.h>

// Timer 0: responsible for system ticks => calls ISR ervery 1ms
void TIMER_init_timer_0(void)
{
	// OCR0A = F_CPU / (prescaler * F_TARGET) - 1
	// OCR0A = 8MHz / (64 * 1kHz) - 1 = 124

	cli();				// deactivate interrupts

	TCCR0A=(1<<0);				// set timer0 to 8 bit ouput compare mode (CTC0-bit but it seems like the header file cant find it => hardcoded / datasheet page 83)
	OCR0A=124;					// set compare value to 124
	TIMSK|=(1<<OCIE0A);			// activate timer0 output compare interrupt
	TCCR0B=(1<<CS01)|(1<<CS00);	// prescaler=64 and start timer

	sei();				// activate interrupts
}


void TIMER_init_timer_1(void)
{
	// for using 8 bit normal mode there are no further setting requiered
	TCCR1A = (1<<COM1B0);	// toggle OC1B pin at compare match (the speaker pin PB3)
}


void TIMER_set_timer_1_frequency(uint16_t frequency)
{
	if(frequency == 0)
	{
		TCCR1B &= ~((1<<CS13) | (1<<CS12) | (1<<CS11) | (1<<CS10));	// stop timer 1
	}
	else
	{
		// frequency calculation
		// f = F_CPU / (Prescaler *(OCR1C + 1))
		// => OCR1C = (F_CPU / Prescaler * f) - 1
		// using prescaler=512 => frequency range: 62Hz - 15,625kHz
		uint32_t ocr_value = (8000000UL / (512L * frequency)) - 1;
		
		if(ocr_value > 255) ocr_value = 255;

		OCR1C = (uint8_t)ocr_value;			// toggle and clear
		OCR1B = (uint8_t)(ocr_value/2);		// just toggle (at 50% duty-cycle)

		// start timer 1
		TCCR1B |= (1<<CS13)| (1<<CS11);		// set prescaler to 512
	}
}