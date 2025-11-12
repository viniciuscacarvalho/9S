/*
 * at_commands_ST87M01.c
 *
 *  Created on: May 2, 2025
 *      Author: viny
 */
#include "at_commands_ST87M01.h"

char return_msg_buffer[AT_COMMANDS_RETURN_MSG_MAX_LEN];

char * get_return_buffer ()
{
	return return_msg_buffer;
}


/* Returns 1  if the Return Size is bigger than the buffer
 * Returns 0  if goes well
 * Returns -1 if the module returns an error
 * */
int at_send_command(const char* command, unsigned int timeout, const unsigned int return_size)
{

	#ifdef __DEBUG_AT_COMMANDS__
	HAL_UART_Transmit_IT(DEBUG_UART, command, strlen(command));
	#endif

	HAL_UART_Transmit(MOBILE_COMMS_UART, command, strlen(command),timeout); //Transmits

	if (return_size > AT_COMMANDS_RETURN_MSG_MAX_LEN)
		return 1;

	HAL_UART_Receive(MOBILE_COMMS_UART, return_msg_buffer, return_size, timeout); //Reads the module

	return_msg_buffer[return_size - 1] = '\0';

	if (strstr(return_msg_buffer,"ERROR"))
		return -1;
	return 0;
}
