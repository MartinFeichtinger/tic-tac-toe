/*
This is a short test program for the speaker. It toggles the speaker pin every two millisecond to generate a pulse signal
500Hz => T=2ms => T_ON = T_OFF = 1ms
*/

#include "config.h"
#include "hal_gpio.h"
#include <util/delay.h>

int main(void)
{
    GPIO_INIT_OUTPUT(SPEAKER);

    while(1)
    {
        GPIO_TOGGLE(SPEAKER);
        //_delay_ms(1);       // make 500Hz sound
        _delay_ms(10000); // 10s stop time test
    } 
}