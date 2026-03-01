#include "hal_timer.h"

// Timer 0: responsible for system ticks => calls ISR ervery 1ms
void TIMER_init_timer_0(void)
{
	// OCR0A = F_CPU / (prescaler * F_TARGET) - 1
	// OCR0A = 1MHz / (8 * 1kHz) - 1 = 124

	cli();				// deactivate interrupts

	TCCR0A=(1<<0);				// set timer0 to 8 bit ouput compare mode (CTC0-bit but it seems like the header file cant find it => hardcoded / datasheet page 83)
	OCR0A=124;					// set compare value to 124
	TIMSK|=(1<<OCIE0A);			// activate timer0 output compare interrupt
	TCCR0B=(1<<CS01)|(1<<CS00);	// prescaler=64 and start timer

	sei();				// activate interrupts
}