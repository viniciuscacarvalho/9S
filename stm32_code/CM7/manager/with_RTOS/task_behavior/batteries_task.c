/*
 * batteries_task.c
 *
 *  Created on: Apr 23, 2025
 *      Author: viny
 */
#include "batteries_task.h"

extern osThreadId_t batterieHandle;

void batterie_task(void *argument)
{
	//setup

	int adc_reading = 0;
	//HAL_UART_Transmit_IT(&huart3, "Batt\n", 6);

	//loop
	while(1)
	{
		HAL_ADC_Start_IT(&hadc1);
		osThreadYield();

		adc_reading = HAL_ADC_GetValue(&hadc1);

			// Start next conversion
		osDelay(ADC_SAMPLE_PERIOD_UC);
	}

}
#ifdef USING_RTOS
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
        osThreadResume(batterieHandle);
}
#endif
