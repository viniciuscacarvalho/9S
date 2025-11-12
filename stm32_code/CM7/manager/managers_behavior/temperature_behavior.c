/*
 * temperature_behavior.h
 *
 *  Created on: Jun 2, 2025
 *      Author: viny
 */

#include "temperature_behavior.h"

void temperature_init (void)
{
	DWT_Init();  // Enable cycle counter for delay
}

void temperature_update (void)
{
	package_data_t* to_send = write_package_data();

	to_send->temperature[to_send->sample_number++ % TEMP_NUMBER_OF_SAMPLES] = DS18B20_GetTemp();
}
