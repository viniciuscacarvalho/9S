/*
 * maneger.c
 *
 *  Created on: Jun 2, 2025
 *      Author: viny
 */
#include "manager.h"

uint64_t current_time;
uint64_t prev_imu_timer = 0;
uint64_t prev_temperature_timer = 0;
uint64_t prev_send_timer = 0;

void manager_init(void)
{
	//Memory
	//init_package_data();
	//Batteries
	//battery_init();
	//Temperature
	//temperature_init();
	//CNSS
	//cnss_init();
	//IMU
	//imu_init();
	//NB_IoT
	nb_iot_init();
	//SD_CARD
	//sd_card_init();

}
void manager_update(void)
{
	current_time = extended_tick;

	if (current_time - prev_imu_timer >= IMU_SAMPLE_PERIOD_UC)
	{
		//IMU
		//imu_update(); //not tested
		prev_imu_timer = current_time;
	}

	if (current_time - prev_temperature_timer >= TEMP_SAMPLE_PERIOD_UC)
	{
		//Temperature
		//temperature_update();
		prev_temperature_timer = current_time;
	}

	if (current_time - prev_send_timer >= SEND_SAMPLE_PERIOD_UC)
	{
		//Batteries
		//battery_update(); //verified
		//CNSS
		//cnss_update(); //working but not tested
		//NB_IoT
		nb_iot_update(); //not working
		///SD_CARD
		//update_package_data();
		//sd_card_update();
		//prev_send_timer = current_time;
	}
	//HAL_Delay(1000);
}
