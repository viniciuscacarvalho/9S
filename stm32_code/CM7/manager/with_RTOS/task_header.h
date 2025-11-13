/*
 * task_header.h
 *
 *  Created on: Apr 23, 2025
 *      Author: viny
 */

#ifndef PROJECT_TASK_HEADER_H_
#define PROJECT_TASK_HEADER_H_
#define USING_RTOS
#include <stdint.h>

#include "../../Core/Inc/main.h"
#include "../package.h"
#include "task_behavior/nb_iot_task.h"
#include "task_behavior/batteries_task.h"
#include "task_behavior/cnss_task.h"
#include "task_behavior/sd_card_task.h"
#include "task_behavior/temp_task.h"
#include "task_behavior/imu_task.h"

#include "../../Core/Inc/usart.h"
//#include "../../Core/Inc/spi.h"
#include "../../Core/Inc/gpio.h"
#include "../../Core/Inc/adc.h"
//#include "../../Core/Inc/tim.h"
//#include "../../FATFS/App/fatfs.h"


//#include "../../Core/Inc/FreeRTOSConfig.h"
//#include <cmsis_os2.h>

extern UART_HandleTypeDef huart3;
//extern TIM_HandleTypeDef htim3;

void idle_task(void *argument);

#include "../defines.h"

#endif /* PROJECT_TASK_HEADER_H_ */
