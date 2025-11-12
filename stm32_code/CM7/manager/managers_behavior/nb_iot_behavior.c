/*
 * nb_iot_behavior.h
 *
 *  Created on: Jun 2, 2025
 *      Author: viny
 */

#include "nb_iot_behavior.h"

void nb_iot_init (void)
{
	#ifdef __DEBUG_AT_COMMANDS__
	HAL_UART_Transmit_IT(DEBUG_UART, MOBILE_COMMS_INIT_MSG, sizeof MOBILE_COMMS_INIT_MSG);
	#endif

	//----------------------------------------
	// 1. COMMUNICATIONS INITIALIZATION
	//----------------------------------------
	at_send_command(
			AT_CMD_LTE_ONLY,
			AT_CMD_LTE_ONLY_TIMEOUT,
			AT_CMD_LTE_ONLY_RETURN_SIZE);
	at_send_command(
			AT_CMD_CAT_M_NB_AUTO,
			AT_CMD_CAT_M_NB_AUTO_TIMEOUT,
			AT_CMD_CAT_M_NB_AUTO_RETURN_SIZE);
	at_send_command(
			AT_CMD_ATTACH_NETWORK,
			AT_CMD_ATTACH_NETWORK_TIMEOUT,
			AT_CMD_ATTACH_NETWORK_RETURN_SIZE);

	at_send_command_with_attempt(
			AT_CMD_NETWORK_STATUS,
			AT_CMD_NETWORK_STATUS_TIMEOUT,
			AT_CMD_NETWORK_STATUS_RETURN_SIZE,
			AT_CMD_NETWORK_STATUS_TRUE_1_RETURN,
			AT_CMD_CONTEXT_STATUS_TRUE_2_RETURN,
			AT_CMD_CONTEXT_STATUS_FALSE_RETURN,
			AT_CMD_NETWORK_STATUS_MAX_ATTEMPTS);


	//----------------------------------------
	// 2. PDP CONTEXT CONFIGURATION
	//----------------------------------------
	char temp_buffer[64];

	sprintf(temp_buffer,AT_CMD_SET_APN,SIMBASE_APN);
	at_send_command(
			temp_buffer,
			AT_CMD_SET_APN_TIMEOUT,
			AT_CMD_SET_APN_RETURN_SIZE);

	at_send_command(
			AT_CMD_ACTIVATE_CONTEXT,
			AT_CMD_ACTIVATE_CONTEXT_TIMEOUT,
			AT_CMD_ACTIVATE_CONTEXT_RETURN_SIZE);
	at_send_command(
			AT_CMD_CONTEXT_STATUS,
			AT_CMD_CONTEXT_STATUS_TIMEOUT,
			AT_CMD_CONTEXT_STATUS_RETURN_SIZE);

	at_send_command_with_attempt(
			AT_CMD_CONTEXT_STATUS,
			AT_CMD_CONTEXT_STATUS_TIMEOUT,
			AT_CMD_CONTEXT_STATUS_RETURN_SIZE,
			AT_CMD_CONTEXT_STATUS_TRUE_1_RETURN,
			AT_CMD_CONTEXT_STATUS_TRUE_2_RETURN,
			AT_CMD_CONTEXT_STATUS_FALSE_RETURN,
			AT_CMD_CONTEXT_STATUS_MAX_ATTEMPTS);

	//----------------------------------------
	// 3. SSL CONFIGURATION
	//----------------------------------------
	at_send_command(
			AT_CMD_SSL_PROFILE,
			AT_CMD_SSL_PROFILE_TIMEOUT,
			AT_CMD_SSL_PROFILE_RETURN_SIZE);
	at_send_command(
			AT_CMD_SSL_VERSION,
			AT_CMD_SSL_VERSION_TIMEOUT,
			AT_CMD_SSL_VERSION_RETURN_SIZE);


	sprintf(temp_buffer,AT_CMD_SSL_SNI,HOST_URL);
	at_send_command(
			temp_buffer,
			AT_CMD_SSL_SNI_TIMEOUT,
			AT_CMD_SSL_SNI_RETURN_SIZE);


	//----------------------------------------
	// 4. HTTP CONFIGURATION
	//----------------------------------------

	sprintf(temp_buffer,AT_CMD_HTTP_URL,HOST_URL);
	at_send_command(
			temp_buffer,
			AT_CMD_HTTP_URL_TIMEOUT,
			AT_CMD_HTTP_URL_RETURN_SIZE);
	at_send_command(
			AT_CMD_HTTP_BODYLEN,
			AT_CMD_HTTP_BODYLEN_TIMEOUT,
			AT_CMD_HTTP_BODYLEN_RETURN_SIZE);
	at_send_command(
			AT_CMD_HTTP_HEADERLEN,
			AT_CMD_HTTP_HEADERLEN_TIMEOUT,
			AT_CMD_HTTP_HEADERLEN_RETURN_SIZE);
	at_send_command(
			AT_CMD_HTTP_TIMEOUT,
			AT_CMD_HTTP_TIMEOUT_TIMEOUT,
			AT_CMD_HTTP_TIMEOUT_RETURN_SIZE);


	//----------------------------------------
	// 5. HTTP REQUEST
	//----------------------------------------
	sprintf(temp_buffer,AT_CMD_HTTP_REQUEST,HOST_URL_PATH);
	sprintf(temp_buffer,temp_buffer,"MSG");
	at_send_command(
			temp_buffer,
			AT_CMD_HTTP_REQUEST_TIMEOUT,
			AT_CMD_HTTP_REQUEST_RETURN_SIZE);
	at_send_command(
			AT_CMD_HTTP_READ,
			AT_CMD_HTTP_READ_TIMEOUT,
			AT_CMD_HTTP_READ_RETURN_SIZE);
	at_send_command(
			AT_CMD_HTTP_DISCONNECT,
			AT_CMD_HTTP_DISCONNECT_TIMEOUT,
			AT_CMD_HTTP_DISCONNECT_RETURN_SIZE);


	//----------------------------------------
	// 6. CLEANUP / SHUTDOWN
	//----------------------------------------
	at_send_command(
			AT_CMD_DEACTIVATE_CONTEXT,
			AT_CMD_DEACTIVATE_CONTEXT_TIMEOUT,
			AT_CMD_DEACTIVATE_CONTEXT_RETURN_SIZE);

	#ifdef __DEBUG_AT_COMMANDS__
	HAL_UART_Transmit_IT(DEBUG_UART, MOBILE_COMMS_END_INIT_MSG, sizeof MOBILE_COMMS_END_INIT_MSG);
	#endif
}

void nb_iot_update (void)
{

	HAL_Delay(1000);
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
