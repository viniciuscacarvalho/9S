/*
 * nb_iot_task.c
 *
 *  Created on: Apr 23, 2025
 *      Author: viny
 */

#include "nb_iot_task.h"
/*
{
  "power_level": 0,
  "temperature": [0, 0, 0],
  "imu": [0, 0, 0],
  "gnss": [
    [0, 0, 0],
    [0, 0, 0]
  ],
  "errors": 0
}
{
	\"power_level\": %u,
	\"temperature\": [%u, %u, %u],
	\"imu\": [%u, %u, %u],
	\"gnss\": [
		[%u, %u, %u],
		[%u, %u, %u]
	],
	\"errors\": %u}
*/
void nb_iot_task(void *argument)
{
	//setup
	package_data_t* ready_to_send;
	char ready_buffer[255];
	char recived_msgs_ac[16];
	ready_to_send = read_package_data();
	sprintf
	(
			ready_buffer,
	"{\"power_level\": %u, \"temperature\": [%u, %u, %u], \"imu\": [%u, %u, %u], \"gnss\": [[%u, %u, %u], [%u, %u, %u]], \"errors\": %u}",
			ready_to_send->power_level,
			ready_to_send->temperature,
			ready_to_send->imu,
			ready_to_send->gnss,
			ready_to_send->errors
	);

	//ac_ping (3, recived_msgs_ac);
	ac_network_attach_request(recived_msgs_ac);
	ac_network_pdp_activate (recived_msgs_ac);
	ac_nb_iot_send	(ready_buffer, sizeof(package_data_t),recived_msgs_ac);

	update_package_data();

	//HAL_UART_Transmit_IT(&huart3, "NB-Iot\n", 7);
	//loop
	while(1)
	{
		osDelay(DELAY_MAX);
	}

}
