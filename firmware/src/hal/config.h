#ifndef CONFIG_H
#define CONFIG_H

// µControler specs: ATtiny461A, Flash=4kB, RAM=256Bytes, CPU=20MHz

// digital output pins
#define ROW0_GREEN	    0, A    //PA0
#define ROW1_GREEN	    2, A    //PA2
#define ROW2_GREEN	    4, A    //PA4
#define ROW0_RED	    1, A    //PA1
#define ROW1_RED	    3, A    //PA3
#define ROW2_RED	    5, A    //PA5
#define COL0		    4, B    //PB4
#define COL1		    5, B    //PB5
#define COL2		    6, B    //PB6
#define SPEAKER		    3, B    //PB3

// analog input pins
#define PLAY_BUTTONS	6, A	//PA6	// two buttons at one pin
#define MODE_SWITCHES   7, A	//PA7	// two switches at one pin

#endif
