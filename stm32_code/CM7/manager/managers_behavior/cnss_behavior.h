/*
 * cnss_behavior.h
 *
 *  Created on: Jun 2, 2025
 *      Author: viny
 */

#ifndef MANAGER_MANAGERS_BEHAVIOR_CNSS_BEHAVIOR_H_
#define MANAGER_MANAGERS_BEHAVIOR_CNSS_BEHAVIOR_H_

#include "../manager.h"

#define AT_CMD_GPS_POWER_ON      "AT+CGNSPWR=1"
#define AT_CMD_GPS_POWER_OFF     "AT+CGNSPWR=0"
#define AT_CMD_GPS_INFO          "AT+CGNSINF"

//GNSS
#define GNSS_PERIOD TIME_BETWEEN_SAMPLES
#define GNSS_RETRY_CONNECTION_DELAY 3000 //ms
#define GNSS_UART &huart1
#define GNSS_ANSWER_LEN 128

#define CONNECTION_FAILED_MSG "Connection Failed\n"
#define GNSS_INIT_MSG "\r\nGNSS Init\r\n"


void cnss_init (void);
void cnss_update (void);

//support functions

char retry_delay(void);

#endif /* MANAGER_MANAGERS_BEHAVIOR_CNSS_BEHAVIOR_H_ */
