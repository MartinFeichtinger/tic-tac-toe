#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include <avr/io.h>
#include "config.h"

// internal gpio action macros
#define _SET_OUTPUT(pin, port)  DDR ## port |= (1 << pin)
#define _SET_INPUT(pin, port)   DDR ## port &= ~(1 << pin)
#define _WRITE_HIGH(pin, port)  PORT ## port |= (1 << pin)
#define _WRITE_LOW(pin, port)   PORT ## port &= ~(1 << pin)
#define _TOGGLE(pin, port)      PORT ## port ^= (1 << pin)
#define _READ(pin, port)        (PIN ## port & (1 << pin))

// public gpio action macros
#define GPIO_INIT_OUTPUT(config) _SET_OUTPUT(config)
#define GPIO_INIT_INPUT(config)  _SET_INPUT(config)
#define GPIO_SET_HIGH(config)    _WRITE_HIGH(config)
#define GPIO_SET_LOW(config)     _WRITE_LOW(config)
#define GPIO_TOGGLE(config)      _TOGGLE(config)
#define GPIO_GET_STATE(config)   _READ(config)

#endif