#ifndef SPEAKER_H
#define SPEAKER_H

#include <stdint.h>

void SPEAKER_init(void);
void SPEAKER_play_sound(uint16_t frequency, uint16_t duration_ms);      // frequency range: 62Hz - 15,625kHz, set to 0 to stop the timer
void SPEAKER_system_tick(void);		                                    // updates the duration coundown and turns off the sound

#endif