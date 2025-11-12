/*
 * maneger.h
 *
 *  Created on: Jun 2, 2025
 *      Author: viny
 */

#ifndef MANAGER_MANAGER_H_
#define MANAGER_MANAGER_H_

//#include "main.h"
#include "../package.h"
#include <stdlib.h>

#include "../../FATFS/App/fatfs.h"
#include "managers_behavior/battery_behavior.h"
#include "managers_behavior/imu_behavior.h"
#include "managers_behavior/cnss_behavior.h"
#include "managers_behavior/nb_iot_behavior.h"
#include "managers_behavior/sd_card_behavior.h"
#include "managers_behavior/temperature_behavior.h"


#include "../../Core/Inc/i2c.h"
#include "../../Core/Inc/usart.h"
#include "../../Core/Inc/sdmmc.h"
//#include "../../Core/Inc/spi.h"
#include "../../Core/Inc/gpio.h"
#include "../../Core/Inc/adc.h"
#include "../../FATFS/App/fatfs.h"

//#include "../../Core/Inc/tim.h"
//#include "../../FATFS/App/fatfs.h"

void manager_init(void);
void manager_update(void);

extern volatile uint64_t extended_tick;

#endif /* MANAGER_MANAGER_H_ */
