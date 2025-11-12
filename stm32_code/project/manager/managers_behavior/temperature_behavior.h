/*
 * temperature_behavior.h
 *
 *  Created on: Jun 2, 2025
 *      Author: viny
 */

#ifndef MANAGER_MANAGERS_BEHAVIOR_TEMPERATURE_BEHAVIOR_H_
#define MANAGER_MANAGERS_BEHAVIOR_TEMPERATURE_BEHAVIOR_H_

#include "../memory.h"
#include "temp_sensor/ds18b20.h"

void temperature_init (void);
void temperature_update (void);

#endif /* MANAGER_MANAGERS_BEHAVIOR_TEMPERATURE_BEHAVIOR_H_ */
