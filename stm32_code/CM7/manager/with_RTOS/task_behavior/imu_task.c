/*
 * imu_task.c
 *
 *  Created on: Apr 23, 2025
 *      Author: viny
 */

#include "imu_task.h"

void imu_task(void *argument)
{
	//setup
	//HAL_UART_Transmit_IT(&huart3, "IMU\n", 4);
	//uint8_t id = imu_spi_read(0x0F);

	//imu_spi_write(0x10, 0x40); // CTRL1_XL: ODR_XL = 104 Hz, FS = ±2g
	//imu_spi_write(0x11, 0x4C); // CTRL2_G: ODR_G = 104 Hz, FS = 2000 dps

	//loop
	while(1)
	{
		//to implement yet
		//osDelay(IMU_SAMPLE_PERIOD_UC);
		HAL_UART_Transmit_IT(&huart3, "Test\n", 6);
		osDelay(1000);
	}

}

void imu_cs_low()  { HAL_GPIO_WritePin(IMU_CS_GPIO_PORT, IMU_CS_PIN, GPIO_PIN_RESET); }
void imu_cs_high() { HAL_GPIO_WritePin(IMU_CS_GPIO_PORT, IMU_CS_PIN, GPIO_PIN_SET); }

int16_t imu_read_axis(uint8_t reg_low)
{
    uint8_t low = imu_spi_read(reg_low);
    uint8_t high = imu_spi_read(reg_low + 1);
    return (int16_t)((high << 8) | low);
}

imu_vector_t imu_read_accel(void)
{
    imu_vector_t accel;
    

    
    IMU 9DOF GY-85 - ITG3205 + ADXL345 + HMC5883L
    accel.x = imu_read_axis(0x28) * 0.061f / 1000.0f;  // ±2g → 0.061 mg/LSB
    accel.y = imu_read_axis(0x2A) * 0.061f / 1000.0f;
    accel.z = imu_read_axis(0x2C) * 0.061f / 1000.0f;
    return accel;
}

imu_vector_t imu_read_gyro(void)
{
    imu_vector_t gyro;
    gyro.x = imu_read_axis(0x22) * 70.0f / 1000.0f;  // 2000 dps → 70 mdps/LSB
    gyro.y = imu_read_axis(0x24) * 70.0f / 1000.0f;
    gyro.z = imu_read_axis(0x26) * 70.0f / 1000.0f;
    return gyro;
}

uint8_t imu_spi_read(uint8_t reg)
{

	uint8_t tx = reg | 0x80;
	uint8_t rx = 0;

	imu_cs_low();
	HAL_SPI_Transmit(&hspi1, &tx, 1, HAL_MAX_DELAY);
	HAL_SPI_Receive(&hspi1, &rx, 1, HAL_MAX_DELAY);
	imu_cs_high();

	return rx;
}

void imu_spi_write(uint8_t reg, uint8_t value) {
    uint8_t tx[2] = { reg & 0x7F, value };

    imu_cs_low();
    HAL_SPI_Transmit(&hspi1, tx, 2, HAL_MAX_DELAY);
    imu_cs_high();
}
