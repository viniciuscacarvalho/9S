/*
 * temp_task.c
 *
 *  Created on: Apr 23, 2025
 *      Author: viny
 */

#include "temp_task.h"

void temp_task(void *argument)
{
	//setup

	//HAL_UART_Transmit_IT(&huart3, "Temp\n", 5);

	Ds18b20_Init((osPriority_t) osPriorityLow);
	//loop
	while(1)
	{
		//one wire comunication
		osDelay(DELAY_MAX);
	}

}

