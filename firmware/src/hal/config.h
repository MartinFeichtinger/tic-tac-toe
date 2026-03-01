#ifndef CONFIG_H
#define CONFIG_H

// µControler specs: ATtiny461A, Flash=4kB, RAM=256Bytes
#define F_CPU 8000000UL  // 8 MHz (8MHz clock with no prescaling) fuse need to be ajusted (from factory the prescaling is x8)
// fuse setting for no prescaling: avrdude -c stk500v2 -P /dev/ttyACM0 -p t461 -U lfuse:w:0xe2:m
// fuse setting for x8 prescaling: avrdude -c stk500v2 -P /dev/ttyACM0 -p t461 -U lfuse:w:0x62:m

// pinout
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// digital output pins
#define LED_ROW0_RED	    0, A    //PA0
#define LED_ROW1_RED	    2, A    //PA2
#define LED_ROW2_RED	    4, A    //PA4
#define LED_ROW0_GREEN	    1, A    //PA1
#define LED_ROW1_GREEN	    3, A    //PA3
#define LED_ROW2_GREEN	    5, A    //PA5
#define LED_COL0		    4, B    //PB4
#define LED_COL1		    5, B    //PB5
#define LED_COL2		    6, B    //PB6
#define SPEAKER		        3, B    //PB3

// analog input pins
#define PLAY_BUTTONS	    6, A	//PA6	// two buttons at one pin
#define MODE_SWITCHES       7, A	//PA7	// two switches at one pin
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
