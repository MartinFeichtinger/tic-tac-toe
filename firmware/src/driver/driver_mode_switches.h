#ifndef DRIVER_MODE_SWTICHES_H
#define DRIVER_MODE_SWTICHES_H

typedef enum
{
	MODE_0 = 0,
	MODE_1 = 1,
	MODE_2 = 2,
	MODE_3 = 3
} mode_t;

void MODE_SWITCHES_init(void);
mode_t MODE_SWITCHES_get_mode(void);

#endif