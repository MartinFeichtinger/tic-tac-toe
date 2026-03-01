#include "driver_led_display.h"
#include "hal_gpio.h"
#include "hal_time.h"


static led_state_t output_buffer[3][6]; // [x][y] => [col][row], row=0: ROW0_GREEN, row=1: ROW0_RED, row=2: ROW1_GREEN, ...
static uint8_t active_row=0;		// for the output buffer => range = 0-5

void LED_DISPLAY_init(void)
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
	
	TIME_set_system_ticks_callback(system_ticks_callback_handler);
}


void LED_DISPLAY_update_buffer(led_state_t led_display_buffer[3][3])
{
	// led_display_buffer[x][y] => [col][row]
	for(uint8_t row=0; row<3; row++)
	{
		for(uint8_t col=0; col<3; col++)
		{
			// clear previous
			output_buffer[col][row*2] = 0;
			output_buffer[col][row*2+1] = 0;

			if(led_display_buffer[col][row] == LED_ON_GREEN)
			{
				output_buffer[col][row*2] = 1;
			}
			else if(led_display_buffer[col][row] == LED_ON_RED)
			{
				output_buffer[col][row*2+1] = 1;
			}
			
		}
	}
}


static void system_ticks_callback_handler(void)
{
	// deactived cols
	GPIO_SET_LOW(LED_COL0);
	GPIO_SET_LOW(LED_COL1);
	GPIO_SET_LOW(LED_COL2);

	// deactived previous row and actived active row
	switch(active_row)
	{
		case 0:
			GPIO_SET_LOW(LED_ROW2_RED);
			GPIO_SET_HIGH(LED_ROW0_GREEN);
			break;
		case 1:
			GPIO_SET_LOW(LED_ROW0_GREEN);
			GPIO_SET_HIGH(LED_ROW0_RED);
			break;
		case 2:
			GPIO_SET_LOW(LED_ROW0_RED);
			GPIO_SET_HIGH(LED_ROW1_GREEN);
			break;
		case 3:
			GPIO_SET_LOW(LED_ROW1_GREEN);
			GPIO_SET_HIGH(LED_ROW1_RED);
			break;
		case 4:
			GPIO_SET_LOW(LED_ROW1_RED);
			GPIO_SET_HIGH(LED_ROW2_GREEN);
			break;
		case 5:
			GPIO_SET_LOW(LED_ROW2_GREEN);
			GPIO_SET_HIGH(LED_ROW2_RED);
			break;
	}

	// activated active cols
	if(output_buffer[0][active_row] == 1) GPIO_SET_HIGH(LED_COL0);
	if(output_buffer[1][active_row] == 1) GPIO_SET_HIGH(LED_COL1);
	if(output_buffer[2][active_row] == 1) GPIO_SET_HIGH(LED_COL2);

	// update active ouput row
	if(active_row >= 5) active_row = 0;
	else active_row++;
}