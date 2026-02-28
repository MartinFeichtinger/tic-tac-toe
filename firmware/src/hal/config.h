#ifndef CONFIG_H
#define CONFIG_H

// µControler specs: ATtiny461A, Flash=4kB, RAM=256Bytes
#define F_CPU 1000000UL  // 1 MHz (8MHz clock with a 8x prescaler)

// pinout
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// digital output pins
#define LED_ROW0_GREEN	    0, A    //PA0
#define LED_ROW1_GREEN	    2, A    //PA2
#define LED_ROW2_GREEN	    4, A    //PA4
#define LED_ROW0_RED	    1, A    //PA1
#define LED_ROW1_RED	    3, A    //PA3
#define LED_ROW2_RED	    5, A    //PA5
#define LED_COL0		    4, B    //PB4
#define LED_COL1		    5, B    //PB5
#define LED_COL2		    6, B    //PB6
#define SPEAKER		        3, B    //PB3

// analog input pins
#define PLAY_BUTTONS	    6, A	//PA6	// two buttons at one pin
#define MODE_SWITCHES       7, A	//PA7	// two switches at one pin
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
