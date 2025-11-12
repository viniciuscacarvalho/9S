/*
 * imu_behavior.h
 *
 *  Created on: Jun 2, 2025
 *      Author: viny
 */

#include "imu_behavior.h"
unsigned int sample_count = 0;

char imu_msg_buffer[32];

void imu_init(void)
{
	uint8_t whoami = 0;
	HAL_I2C_Mem_Read(IMU_I2C, ITG3205_ADDR, 0x00, I2C_MEMADD_SIZE_8BIT, &whoami, 1, 100);
	sprintf(imu_msg_buffer, "\r\nWHO_AM_I: 0x%02X\r\n", whoami);
	HAL_UART_Transmit(DEBUG_UART, imu_msg_buffer, 20, -1);

	uint8_t val;

	// Sample Rate Divider
	val = 0x07;
	HAL_I2C_Mem_Write(IMU_I2C, ITG3205_ADDR, 0x15, I2C_MEMADD_SIZE_8BIT, &val, 1, 100);

	// DLPF & Full Scale
	val = 0x1B;
	HAL_I2C_Mem_Write(IMU_I2C, ITG3205_ADDR, 0x16, I2C_MEMADD_SIZE_8BIT, &val, 1, 100);

	// Power Management
	val = 0x03;
	HAL_I2C_Mem_Write(IMU_I2C, ITG3205_ADDR, 0x3E, I2C_MEMADD_SIZE_8BIT, &val, 1, 100);

	HAL_UART_Transmit(DEBUG_UART, IMU_INIT_MSG , sizeof IMU_INIT_MSG , 100);

}

void imu_update(void)
{
	if (sample_count < IMU_NUMBER_OF_SAMPLES)
	{
		uint8_t buf[2] = {0};
		if (HAL_I2C_Mem_Read(IMU_I2C, ITG3205_ADDR, 0x21, I2C_MEMADD_SIZE_8BIT, buf, 2, 100) == HAL_OK)
		{
			int16_t z_raw = (int16_t)((buf[0] << 8) | buf[1]);
			package_data_t* imu_data = write_package_data();
			imu_data->imu[sample_count] = z_raw;
			sample_count++;

			sprintf(imu_msg_buffer, "\r\nZ: %02X %02X = %d\r\n", buf[0], buf[1], z_raw);
			HAL_UART_Transmit(DEBUG_UART, imu_msg_buffer, strlen(imu_msg_buffer), 100);
		}
	}
	else {
		sample_count = 0;
	}
}

