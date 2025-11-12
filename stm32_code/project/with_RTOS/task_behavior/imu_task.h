/*
 * imu_task.h
 *
 *  Created on: Apr 23, 2025
 *      Author: viny
 */

#ifndef PROJECT_TASK_BEHAVIOR_IMU_TASK_H_
#define PROJECT_TASK_BEHAVIOR_IMU_TASK_H_

#include "../task_header.h"

typedef struct {
    float x, y, z;
} imu_vector_t;

void imu_task(void *argument);
void imu_cs_low();
void imu_cs_high();
uint8_t imu_spi_read(uint8_t reg);
void imu_spi_write(uint8_t reg, uint8_t value);
int16_t imu_read_axis(uint8_t reg_low);
imu_vector_t imu_read_accel(void);
imu_vector_t imu_read_gyro(void);




#endif /* PROJECT_TASK_BEHAVIOR_IMU_TASK_H_ */
