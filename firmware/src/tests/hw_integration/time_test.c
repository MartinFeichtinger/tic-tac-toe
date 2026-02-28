#include "hal_time.h"
#include "hal_gpio.h"
//#include <util/delay.h>


int main(void)
{
	// init gpios
	GPIO_INIT_OUTPUT(LED_ROW0_GREEN);
	GPIO_INIT_OUTPUT(LED_COL0);

	// init timer
	TIMER_init_timer_0();

	GPIO_SET_HIGH(LED_ROW0_GREEN);

	while(1)
	{
		uint32_t start_time=TIME_get_millis();

		// wait 1000ms based on the system tick timer
		while((TIME_get_millis() - start_time) < 1000);

		//_delay_ms(1000);
		GPIO_TOGGLE(LED_COL0);
	}
}
