/*
 * battery_behavior.h
 *
 *  Created on: Jun 2, 2025
 *      Author: viny
 */
#include "battery_behavior.h"

void battery_init (void)
{

}

void battery_update (void)
{
	//Start Conversion
	HAL_ADC_Start(&hadc1);

	//Get and Store Conversion
	package_data_t* temp = write_package_data();
	temp->power_level=
			((HAL_ADC_GetValue(&hadc1) * 5/1023)-3.3)/0.017;
	char buffer[16];
	sprintf(buffer,"Batt:%d\n\n",(int)temp->power_level);
	HAL_UART_Transmit(&huart3, buffer, 8, -1);
}



#ifndef USING_RTOS
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
        //
}
#endif
