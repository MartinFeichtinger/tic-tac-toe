#ifndef CONFIG_H
#define CONFIG_H

// µControler specs: ATtiny461A, RAM=4KB, CPU=20MHz

#include <avr/io.h>
#include <avr/interrupt.h>

// digital output pins
#define ROW0_GREEN	    PA0
#define ROW1_GREEN	    PA2
#define ROW2_GREEN	    PA4
#define ROW0_RED	    PA1
#define ROW1_RED	    PA3
#define ROW2_RED	    PA5
#define COL0		    PB4
#define COL1		    PB5
#define COL2		    PB6
#define SPEAKER		    PB3

// analog input pins
#define PLAY_BUTTONS	PA6		// two buttons at one pin
#define MODE_SWITCHES   PA7		// two switches at one pin

#endif
