#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include <avr/io.h>
#include "config.h"

// internal gpio action macros
#define _INIT_OUTPUT(pin, port)		DDR ## port |= (1 << pin)
#define _INIT_INPUT(pin, port)		DDR ## port &= ~(1 << pin)
#define _SET_HIGH(pin, port)		PORT ## port |= (1 << pin)
#define _SET_LOW(pin, port)			PORT ## port &= ~(1 << pin)
#define _TOGGLE(pin, port)			PORT ## port ^= (1 << pin)
#define _READ(pin, port)			(PIN ## port & (1 << pin))

// public gpio action macros
#define GPIO_INIT_OUTPUT(config)	_INIT_OUTPUT(config)
#define GPIO_INIT_INPUT(config)		_INIT_INPUT(config)
#define GPIO_SET_HIGH(config)		_SET_HIGH(config)
#define GPIO_SET_LOW(config)		_SET_LOW(config)
#define GPIO_TOGGLE(config)			_TOGGLE(config)
#define GPIO_READ(config)			_READ(config)

#endif