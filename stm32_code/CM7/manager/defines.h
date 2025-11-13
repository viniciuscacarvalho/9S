/*
 * defines.h
 *
 *  Created on: Apr 23, 2025
 *      Author: viny
 */

#ifndef PROJECT_DEFINES_H_
#define PROJECT_DEFINES_H_

#include <stdint.h>

#define DELAY_MAX (unsigned int)-1

#define ERROR_MSG "\r\nError Handler\r\n"
#define NUMBER_OF_SAMPLES 10

#define TIME_BETWEEN_SAMPLES 10 //in minutes

#define SEND_SAMPLE_PERIOD_UC 10000//600
#define DEBUG_UART &huart3
#define DEBUG_ANSWER_LEN 64
//ADC
#define ADC_SAMPLE_PERIOD_UC SEND_SAMPLE_PERIOD_UC
#define BATTERY_MAX_VOLTAGE 3.9
#define BATTERY_MAX_VOLTAGE_OVER_10BIT 1/((1<<10)/5)

//SD card

#define SD_CARD_INIT_MSG "\r\nSD Card Init\r\n"

//IMU
//#define IMU_CS_GPIO_PORT GPIOC
//#define IMU_CS_PIN GPIO_PIN_0
#define IMU_SAMPLE_PERIOD_UC 5000
#define IMU_SAMPLE_FREQUENCY 5
#define IMU_NUMBER_OF_SAMPLES TIME_BETWEEN_SAMPLES * 60 * IMU_SAMPLE_FREQUENCY

#define ADXL345_ADDR   (0x53 << 1)  // ACCEL
#define ITG3205_ADDR   (0x68 << 1)  // GYRO
#define HMC5883L_ADDR  (0x1E << 1)  // MAG

#define IMU_I2C &hi2c1

#define IMU_INIT_MSG "\r\nIMU Ready\r\n"

//Temp
#define ONEWIRE_PORT GPIOC
#define ONEWIRE_PIN GPIO_PIN_0
#define TEMP_NUMBER_OF_SAMPLES TIME_BETWEEN_SAMPLES
#define TEMP_SAMPLE_PERIOD_UC  5000//1000*60*TIME_BETWEEN_SAMPLES/TEMP_NUMBER_OF_SAMPLES

//#define TEMP_SENSOR_TIMER htim3

//BOTH GNSS AND MOBILE

#define COMMAND_GENERAL_DELAY 1300

#endif /* PROJECT_DEFINES_H_ */
