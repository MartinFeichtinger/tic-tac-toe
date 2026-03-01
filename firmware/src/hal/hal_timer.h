#ifndef HAL_TIMER_H
#define HAL_TIMER_H

#include <stdint.h>

// Timer 0: system tick generator
void TIMER_init_timer_0(void);

// Timer 1: pwm generator for the speaker
void TIMER_init_timer_1(void);
void TIMER_set_timer_1_frequency(uint16_t frequency);	// frequency range: 62Hz - 15,625kHz, set to 0 to stop the timer

#endif