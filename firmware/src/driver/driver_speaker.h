#ifndef SPEAKER_H
#define SPEAKER_H

#include <stdint.h>

void SPEAKER_init(void);
void SPEAKER_play_sound(uint16_t frequency, uint16_t duration_ms);
void SPEAKER_system_tick(void);		// updates the duration coundown and turns off the sound

#endif