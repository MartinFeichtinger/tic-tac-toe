/*
This is a test program for the led display. It should test the fuctionality of each led on the display.
Therfore it set on led afer another to red and then green to detect hardware errors and errors in the config.h

!! Warning !!
Do not switch on two different rows and colors at once. The scematic isn't concepted for this. Therfore we need some mutiplexing later...
*/
#include <util/delay.h>
#include <stdint.h>
#include "config.h"
#include "hal_gpio.h"

#define GREEN   0
#define RED     1

void switch_on_led(uint8_t row, uint8_t col, uint8_t color);
void switch_off_led(uint8_t row, uint8_t col, uint8_t color);

int main(void)
{
    GPIO_INIT_OUTPUT(LED_ROW0_GREEN);
    GPIO_INIT_OUTPUT(LED_ROW1_GREEN);
    GPIO_INIT_OUTPUT(LED_ROW2_GREEN);
    GPIO_INIT_OUTPUT(LED_ROW0_RED);
    GPIO_INIT_OUTPUT(LED_ROW1_RED);
    GPIO_INIT_OUTPUT(LED_ROW2_RED);
    GPIO_INIT_OUTPUT(LED_COL0);
    GPIO_INIT_OUTPUT(LED_COL1);
    GPIO_INIT_OUTPUT(LED_COL2);

    GPIO_SET_LOW(LED_ROW0_GREEN);
    GPIO_SET_LOW(LED_ROW1_GREEN);
    GPIO_SET_LOW(LED_ROW2_GREEN);
    GPIO_SET_LOW(LED_ROW0_RED);
    GPIO_SET_LOW(LED_ROW1_RED);
    GPIO_SET_LOW(LED_ROW2_RED);
    GPIO_SET_LOW(LED_COL0);
    GPIO_SET_LOW(LED_COL1);
    GPIO_SET_LOW(LED_COL2);


    while(1)
    {
        // test each led for green
        for(uint8_t row=0; row<3; row++)
        {
            for(uint8_t col=0; col<3; col++)
            {
                switch_on_led(row, col, GREEN);
                _delay_ms(1000);
                switch_off_led(row, col, GREEN);
            }
        }

        // test each led for red
        for(uint8_t row=0; row<3; row++)
        {
            for(uint8_t col=0; col<3; col++)
            {
                switch_on_led(row, col, RED);
                _delay_ms(1000);
                switch_off_led(row, col, RED);
            }
        }
    }
}

void switch_on_led(uint8_t row, uint8_t col, uint8_t color)
{
    switch(row)
    {
        case 0:
            switch(color)
            {
                case GREEN:
                    GPIO_SET_HIGH(LED_ROW0_GREEN);
                    break;
                case RED:
                    GPIO_SET_HIGH(LED_ROW0_RED);
                    break;
            }
            break;
        case 1:
            switch(color)
            {
                case GREEN:
                    GPIO_SET_HIGH(LED_ROW1_GREEN);
                    break;
                case RED:
                    GPIO_SET_HIGH(LED_ROW1_RED);
                    break;
            }            
            break;
        case 2:
            switch(color)
            {
                case GREEN:
                    GPIO_SET_HIGH(LED_ROW2_GREEN);
                    break;
                case RED:
                    GPIO_SET_HIGH(LED_ROW2_RED);
                    break;
            }
            break;
    }

    switch(col)
    {
        case 0:
            GPIO_SET_HIGH(LED_COL0);
            break;
        case 1:
            GPIO_SET_HIGH(LED_COL1);
            break;
        case 2:
            GPIO_SET_HIGH(LED_COL2);
            break;
    }
}

void switch_off_led(uint8_t row, uint8_t col, uint8_t color)
{
    switch(row)
    {
        case 0:
            switch(color)
            {
                case GREEN:
                    GPIO_SET_LOW(LED_ROW0_GREEN);
                    break;
                case RED:
                    GPIO_SET_LOW(LED_ROW0_RED);
                    break;
            }
            break;
        case 1:
            switch(color)
            {
                case GREEN:
                    GPIO_SET_LOW(LED_ROW1_GREEN);
                    break;
                case RED:
                    GPIO_SET_LOW(LED_ROW1_RED);
                    break;
            }            
            break;
        case 2:
            switch(color)
            {
                case GREEN:
                    GPIO_SET_LOW(LED_ROW2_GREEN);
                    break;
                case RED:
                    GPIO_SET_LOW(LED_ROW2_RED);
                    break;
            }
            break;
    }
    
    switch(col)
    {
        case 0:
            GPIO_SET_LOW(LED_COL0);
            break;
        case 1:
            GPIO_SET_LOW(LED_COL1);
            break;
        case 2:
            GPIO_SET_LOW(LED_COL2);
            break;
    }    
}