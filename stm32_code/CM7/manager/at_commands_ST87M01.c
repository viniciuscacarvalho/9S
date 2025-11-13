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

int at_send_command_with_attempt(
    const char *command,
    unsigned int timeout,
    unsigned int return_size,
    const char *true_str_1,
    const char *true_str_2,
    const char *false_str,
    unsigned int attempt_number)
{
    for (unsigned int i = 0; i < (attempt_number - 1); i++)
    {
        uint32_t start = HAL_GetTick();

        at_send_command(command, timeout, return_size);

        char *resp = get_return_buffer();

        if ( ((true_str_1 && strstr(resp, true_str_1)) ||
              (true_str_2 && strstr(resp, true_str_2))) &&
             (!false_str || strstr(resp, false_str) == NULL) )
        {
            return 0;
        }

        // Wait ~1 second before retry
        while ((HAL_GetTick() - start) < 1000UL);
    }

    // Final attempt (no wait)
    at_send_command(command, timeout, return_size);
    char *resp = get_return_buffer();

    if ( ((true_str_1 && strstr(resp, true_str_1)) ||
          (true_str_2 && strstr(resp, true_str_2))) &&
         (!false_str || strstr(resp, false_str) == NULL) )
    {
        return 0;
    }

    return -1; // Failed all attempts
}
