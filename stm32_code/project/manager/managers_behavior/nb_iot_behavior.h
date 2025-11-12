/*
 * nb_iot_behavior.h
 *
 *  Created on: Jun 2, 2025
 *      Author: viny
 */

#ifndef MANAGER_MANAGERS_BEHAVIOR_NB_IOT_BEHAVIOR_H_
#define MANAGER_MANAGERS_BEHAVIOR_NB_IOT_BEHAVIOR_H_

#include "../manager.h"

/*Command list for a HTTP get
	 *
	 * ----------------------------------------
	 * Init
		AT
		ATE0
		AT+CMEE=2
		AT+CNMP=38
		AT+CMNB=3
		AT+CGATT=1
	 * Clock Sync
		AT+CCLK?
		AT+CLTS=1
		AT+CCLK?
	 * PDP Context ON
	  	AT+CGDCONT=1,"IP","<APN>"
		AT+CNACT=1,1
	 * SSL Config
		AT+SHSSL=1,""
		AT+CSSLCFG="sslversion",1,3
		AT+CSSLCFG="sni",1,"<URL_HOST>"
	 * HTTP Config
		AT+SHCONF="URL","https://<URL_HOST>"
		AT+SHCONF="BODYLEN",1024
		AT+SHCONF="HEADERLEN",350
		AT+SHCONF="TIMEOUT",200
	 * GET request
	 	AT+SHREQ="<GET_PATH>",1
	 * End transmition
		AT+SHREAD=1,500
		AT+SHDISC
		AT+CNACT=0

	 * ----------------------------------------
	 * */

#define HOST_URL "inovtex.com"
#define SIMBASE_APN "simbase"
#define HOST_URL_PATH "/testes/vinicius/?t=%s/"

#define AT_CMD_LTE_ONLY                   "\r\nAT+CNMP=38\r\n"
#define AT_CMD_LTE_ONLY_TIMEOUT           2000
#define AT_CMD_LTE_ONLY_RETURN_SIZE       32

#define AT_CMD_CAT_M_NB_AUTO              "\r\nAT+CMNB=3\r\n"
#define AT_CMD_CAT_M_NB_AUTO_TIMEOUT      2000
#define AT_CMD_CAT_M_NB_AUTO_RETURN_SIZE  32

#define AT_CMD_ATTACH_NETWORK             "\r\nAT+CGATT=1\r\n"
#define AT_CMD_ATTACH_NETWORK_TIMEOUT     5000
#define AT_CMD_ATTACH_NETWORK_RETURN_SIZE 64

// ========== NETWORK REGISTRATION ==========
#define AT_CMD_NETWORK_STATUS             "\r\nAT+CEREG?\r\n"
#define AT_CMD_NETWORK_STATUS_TIMEOUT     3000
#define AT_CMD_NETWORK_STATUS_RETURN_SIZE 64
#define AT_CMD_NETWORK_STATUS_TRUE_1_RETURN "0,5"
#define AT_CMD_NETWORK_STATUS_TRUE_2_RETURN "0,1"
#define AT_CMD_NETWORK_STATUS_FALSE_RETURN NULL
#define AT_CMD_NETWORK_STATUS_MAX_ATTEMPTS 10


// ========== PDP CONTEXT ==========
#define AT_CMD_SET_APN                    "\r\nAT+CGDCONT=1,\"IP\",\"%s\"\r\n"   // Use sprintf for APN
#define AT_CMD_SET_APN_TIMEOUT            2000
#define AT_CMD_SET_APN_RETURN_SIZE        32

#define AT_CMD_ACTIVATE_CONTEXT           "\r\nAT+CNACT=1,1\r\n"
#define AT_CMD_ACTIVATE_CONTEXT_TIMEOUT   5000
#define AT_CMD_ACTIVATE_CONTEXT_RETURN_SIZE 128

#define AT_CMD_CONTEXT_STATUS             "\r\nAT+CNACT?\r\n"
#define AT_CMD_CONTEXT_STATUS_TIMEOUT     2000
#define AT_CMD_CONTEXT_STATUS_RETURN_SIZE 64
#define AT_CMD_CONTEXT_STATUS_TRUE_1_RETURN "+CNACT: 1,1"
#define AT_CMD_CONTEXT_STATUS_TRUE_2_RETURN NULL
#define AT_CMD_CONTEXT_STATUS_FALSE_RETURN "\"0.0.0.0\""
#define AT_CMD_CONTEXT_STATUS_MAX_ATTEMPTS 10

#define AT_CMD_DEACTIVATE_CONTEXT         "\r\nAT+CNACT=0\r\n"
#define AT_CMD_DEACTIVATE_CONTEXT_TIMEOUT 2000
#define AT_CMD_DEACTIVATE_CONTEXT_RETURN_SIZE 32


// ========== SSL CONFIGURATION ==========
#define AT_CMD_SSL_PROFILE                "\r\nAT+SHSSL=1,\"\"\r\n"
#define AT_CMD_SSL_PROFILE_TIMEOUT        2000
#define AT_CMD_SSL_PROFILE_RETURN_SIZE    32

#define AT_CMD_SSL_VERSION                "\r\nAT+CSSLCFG=\"sslversion\",1,3\r\n"
#define AT_CMD_SSL_VERSION_TIMEOUT        2000
#define AT_CMD_SSL_VERSION_RETURN_SIZE    32

#define AT_CMD_SSL_SNI                    "\r\nAT+CSSLCFG=\"sni\",1,\"%s\"\r\n"  // Hostname as parameter
#define AT_CMD_SSL_SNI_TIMEOUT            3000
#define AT_CMD_SSL_SNI_RETURN_SIZE        64


// ========== HTTP CONFIGURATION ==========
#define AT_CMD_HTTP_URL                   "\r\nAT+SHCONF=\"URL\",\"https://%s\"\r\n" // %s = host
#define AT_CMD_HTTP_URL_TIMEOUT           2000
#define AT_CMD_HTTP_URL_RETURN_SIZE       64

#define AT_CMD_HTTP_BODYLEN               "\r\nAT+SHCONF=\"BODYLEN\",1024\r\n"
#define AT_CMD_HTTP_BODYLEN_TIMEOUT       1000
#define AT_CMD_HTTP_BODYLEN_RETURN_SIZE   32

#define AT_CMD_HTTP_HEADERLEN             "\r\nAT+SHCONF=\"HEADERLEN\",350\r\n"
#define AT_CMD_HTTP_HEADERLEN_TIMEOUT     1000
#define AT_CMD_HTTP_HEADERLEN_RETURN_SIZE 32

#define AT_CMD_HTTP_TIMEOUT               "\r\nAT+SHCONF=\"TIMEOUT\",200\r\n"
#define AT_CMD_HTTP_TIMEOUT_TIMEOUT       1000
#define AT_CMD_HTTP_TIMEOUT_RETURN_SIZE   32


// ========== HTTP OPERATIONS ==========
#define AT_CMD_HTTP_REQUEST               "\r\nAT+SHREQ=\"%s\",1\r\n"   // %s = path
#define AT_CMD_HTTP_REQUEST_TIMEOUT       15000
#define AT_CMD_HTTP_REQUEST_RETURN_SIZE   512

#define AT_CMD_HTTP_READ                  "\r\nAT+SHREAD=1,500\r\n"
#define AT_CMD_HTTP_READ_TIMEOUT          5000
#define AT_CMD_HTTP_READ_RETURN_SIZE      1024

#define AT_CMD_HTTP_DISCONNECT            "\r\nAT+SHDISC\r\n"
#define AT_CMD_HTTP_DISCONNECT_TIMEOUT    2000
#define AT_CMD_HTTP_DISCONNECT_RETURN_SIZE 32


#define MAX_SEND_ATTEMPTS 10


#define __DEBUG_AT_COMMANDS__
//debug msgs
#ifdef __DEBUG_AT_COMMANDS__
#define MOBILE_COMMS_INIT_MSG "\r\nMobile Comms Init\r\n"
#define MOBILE_COMMS_END_INIT_MSG "\r\nMobile Comms Init END\r\n"
#endif


void nb_iot_init (void);

void nb_iot_update (void);

int at_send_command_with_attempt(
    const char *command,
    unsigned int timeout,
    unsigned int return_size,
    const char *true_str_1,
    const char *true_str_2,
    const char *false_str,
    unsigned int attempt_number)
{
#endif /* MANAGER_MANAGERS_BEHAVIOR_NB_IOT_BEHAVIOR_H_ */
