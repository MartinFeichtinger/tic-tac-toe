#ifndef HAL_TIME_H
#define HAL_TIME_H

#include "hal_timer.h"
#include <stdint.h>

uint32_t TIME_get_millis(void);
void TIME_delay_ms(uint16_t ms);

typedef void (*TIME_system_ticks_callback_t)(void);
void TIME_set_system_ticks_callback(TIME_system_ticks_callback_t callback);

#endif