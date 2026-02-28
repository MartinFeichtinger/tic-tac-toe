#ifndef HAL_ADC_H
#define HAL_ADC_H

#include <avr/io.h>
#include <stdint.h>

void ADC_init(void);
uint16_t _ADC_read(uint8_t pin, uint8_t port);

// macro definition for the port pin mapping
#define _ADC_READ(pin, port)	_ADC_read(pin, DDR ## port);
#define ADC_READ(config)		_ADC_READ(config)

#endif