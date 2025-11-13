/*
 * at_commands_ST87M01.h
 *
 *  Created on: May 2, 2025
 *      Author: viny
 */

#ifndef PROJECT_AT_COMMANDS_ST87M01_H_
#define PROJECT_AT_COMMANDS_ST87M01_H_

#include "manager.h"
#include <string.h>

//Init At commands
// ===== General Module Commands =====
#define AT_CMD_TEST              "\r\nAT\r\n"
#define AT_CMD_DISABLE_ECHO      "\r\nATE0\r\n"
#define AT_CMD_VERBOSE_ERRORS    "\r\nAT+CMEE=2\r\n"
#define AT_CMD_GET_CLOCK         "\r\nAT+CCLK?\r\n"
#define AT_CMD_ENABLE_NET_TIME   "\r\nAT+CLTS=1\r\n"

#define AT_COMMANDS_RETURN_MSG_MAX_LEN 96
//ERROR msgs go up to 20 chars but GNSS go way more, so
//32 bytes + 64 bytes for betther memory alocation

#define MOBILE_COMMS_UART &huart3

int at_send_command(const char* command, unsigned int timeout, const unsigned int return_size);

int at_send_command_with_attempt(
    const char *command,
    unsigned int timeout,
    unsigned int return_size,
    const char *true_str_1,
    const char *true_str_2,
    const char *false_str,
    unsigned int attempt_number);


#endif /* PROJECT_AT_COMMANDS_ST87M01_H_ */
