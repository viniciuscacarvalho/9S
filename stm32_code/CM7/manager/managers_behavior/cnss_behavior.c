/*
 * cnss_behavior.h
 *
 *  Created on: Jun 2, 2025
 *      Author: viny
 */

#include "cnss_behavior.h"

char recived_buffer_gnss[GNSS_ANSWER_LEN] = {0};
char recived_buffer_debug[DEBUG_ANSWER_LEN] = {0};
char buffer[64];
char gnss_run_status;
char utc_temp[32];

void cnss_init (void)
{
	//HAL_UART_Transmit_IT(DEBUG_UART, GNSS_INIT_MSG, sizeof GNSS_INIT_MSG);
	HAL_Delay(1000);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET); // PWRKEY HIGH
	HAL_Delay(1200);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);   // PWRKEY LOW
	HAL_Delay(4000);  // wait boot

	at_echo_off (recived_buffer_debug); // turn off echo function
	sprintf(buffer,"\r\nEcho off:%s\r\n",recived_buffer_debug);
	HAL_UART_Transmit(DEBUG_UART, buffer, 16, -1);

	at_set_baudrate (recived_buffer_debug);
	sprintf(buffer,"\r\nBaudrate:%s\r\n",recived_buffer_debug);
	HAL_UART_Transmit(DEBUG_UART, buffer, 16, -1);

	at_power_on(recived_buffer_debug); // turn on the GNSS
	sprintf(buffer,"\r\nOn:%s\r\n",recived_buffer_debug);
	HAL_UART_Transmit(DEBUG_UART, buffer, 16, -1);


}

void cnss_update (void)
{


	do{
		memset(recived_buffer_debug, 0, DEBUG_ANSWER_LEN);
		at_power_state(recived_buffer_debug); //ask if the module is ready
		HAL_Delay(100);
		memset(buffer, 0, sizeof buffer);
		sprintf(buffer,"\r\nVerification:%s\r\n",recived_buffer_debug);

		HAL_UART_Transmit(DEBUG_UART, buffer, 32,-1);

		sscanf(recived_buffer_debug,"\r\n+CGNSPWR: %d",&gnss_run_status);
	}while(!(gnss_run_status || retry_delay()));

	memset(recived_buffer_gnss, 0, GNSS_ANSWER_LEN);

	at_gnss_signal(recived_buffer_gnss);

	package_data_t * gnss_info = write_package_data();
	char dummy;
	sscanf(recived_buffer_gnss,
	       "\r\n+CGNSINF: %d,%c,%[^,],%f,%f"
			,&gnss_run_status
			,&dummy
			,utc_temp
			,&gnss_info->gnss.latitude
			,&gnss_info->gnss.longitude);

	sscanf(utc_temp, "%4d%2d%2d%2d%2d%2d"
			, &gnss_info->utc.year
			, &gnss_info->utc.month
			, &gnss_info->utc.day
			, &gnss_info->utc.hour
			, &gnss_info->utc.minute
			, &gnss_info->utc.second);

	//debug
	//HAL_Delay(1000);
	memset(recived_buffer_gnss, 0, GNSS_ANSWER_LEN);
	memset(buffer, 0, sizeof (buffer));
	sprintf(buffer,"\r\nGNSS:\n\tLat:%f\n\tLong:%f\r\n"
			,gnss_info->gnss.latitude
			,gnss_info->gnss.longitude);

	HAL_UART_Transmit(DEBUG_UART, buffer,GNSS_ANSWER_LEN,1000);

}

char retry_delay(void)
{
	//HAL_UART_Transmit(DEBUG_UART, CONNECTION_FAILED_MSG, sizeof(CONNECTION_FAILED_MSG),-1);
	HAL_Delay(100);
	HAL_UART_Transmit(DEBUG_UART, "Retrying GNSS data\n",sizeof("Retrying GNSS data\n"),-1);


	memset(buffer, 0, sizeof buffer);
	memset(recived_buffer_debug, 0, DEBUG_ANSWER_LEN);
	at_power_off(recived_buffer_debug); // turn on the GNSS
	sprintf(buffer,"Turning OFF:%s\n",recived_buffer_debug);
	HAL_UART_Transmit(DEBUG_UART, buffer, 32, -1);

	//HAL_Delay(GNSS_RETRY_CONNECTION_DELAY);

	memset(buffer, 0, sizeof buffer);
	memset(recived_buffer_debug, 0, DEBUG_ANSWER_LEN);
	at_power_on(recived_buffer_debug); // turn on the GNSS
	sprintf(buffer,"Turning ON:%s\n",recived_buffer_debug);
	HAL_UART_Transmit(DEBUG_UART, buffer, 32, -1);

	return 0;
}
