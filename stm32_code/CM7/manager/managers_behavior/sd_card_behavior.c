/*
 * sd_card_behavior.h
 *
 *  Created on: Jun 2, 2025
 *      Author: viny
 */

#include "sd_card_behavior.h"

// File system object
FATFS fs;
// File object
FIL fil;
// Result code
FRESULT res;
// File write count
UINT bw;
char verify_flag;
char to_send[512];

void sd_card_init (void)
{
    // Mount SD Card
    HAL_UART_Transmit(DEBUG_UART, SD_CARD_INIT_MSG , sizeof SD_CARD_INIT_MSG , -1);

    if (HAL_SD_Init(&hsd1) != HAL_OK)
	{
		Error_Handler();
	}

    //SD_initialize(lun)
    for (int i = 0,verify_flag = 0; (i < 10) & !verify_flag; ++i)
    {
        if (HAL_SD_GetCardState(&hsd1) == HAL_SD_CARD_TRANSFER)
        {
        	verify_flag = 1;
        }
        HAL_Delay(50);
    }

    if (BSP_SD_Init() != RES_OK)
   {
	   Error_Handler();
   }

    if (disk_initialize(0) != RES_OK)
   {
	   Error_Handler();
   }

    res = f_mount(&fs, (TCHAR const*)SDPath, 1);
    if (res != FR_OK)
    {
        Error_Handler();
    }
}

void sd_card_update (void)
{
    package_data_t* data = read_package_data();

    // Open or create file to write
    char log_name[16];
    sprintf(log_name,"log_%d.txt",data->packege_number);
    res = f_open(&fil, log_name, FA_WRITE | FA_CREATE_ALWAYS);
    if (res != FR_OK)
    {
        Error_Handler();
    }
    uint32_t offset = 0;

    offset += snprintf(to_send + offset, sizeof(to_send) - offset,
        "Power: %d V\n"
        "Time: %04d-%02d-%02d %02d:%02d:%02d\n"
        "GNSS: Lat=%f, Lon=%f\n"
        "Temp:",
        data->power_level,
        data->utc.year, data->utc.month, data->utc.day,
        data->utc.hour, data->utc.minute, data->utc.second,
        data->gnss.latitude, data->gnss.longitude);

    for (int i = 0; i < TEMP_NUMBER_OF_SAMPLES; i++) {
        offset += snprintf(to_send + offset-4, strlen(to_send), " %d", data->temperature[i]);
    }

    offset += snprintf(to_send + offset-4, strlen(to_send), "\nIMU:");

    for (int i = 0; i < IMU_NUMBER_OF_SAMPLES; i++) {
        offset += snprintf(to_send + offset-4, strlen(to_send), " %d", data->imu[i]);
    }

    offset += snprintf(to_send + offset-4, strlen(to_send),
        "\nErrors: 0x%04X\nSample #: %u\n------------------\n",
        data->errors, data->sample_number);


    // Write a string to the file
    HAL_UART_Transmit(DEBUG_UART,to_send,strlen(to_send),-1);
    res = f_write(&fil, to_send, strlen(to_send), &bw);
    if (res != FR_OK || bw < strlen(to_send))
    {
        Error_Handler();
    }

    // Close the file
    f_close(&fil);
}
