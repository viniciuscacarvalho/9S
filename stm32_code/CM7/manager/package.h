/*
 * package.h
 *
 *  Created on: May 1, 2025
 *      Author: viny
 */

#ifndef PROJECT_TASK_BEHAVIOR_PACKAGE_H_
#define PROJECT_TASK_BEHAVIOR_PACKAGE_H_

#include "defines.h"

typedef struct
{
	float longitude;
	float latitude;
} coordinates_t;

typedef struct
{
    int year;        // e.g., 2025
    int month;       // 1 to 12
    int day;         // 1 to 31
    int hour;        // 0 to 23
    int minute;      // 0 to 59
    int second;      // 0 to 59
    //int millisecond; // 0 to 999
} utc_time_t;

typedef struct
{
    float power_level;
    utc_time_t utc;
    unsigned short temperature[TEMP_NUMBER_OF_SAMPLES];
    int16_t imu[IMU_NUMBER_OF_SAMPLES];
    coordinates_t gnss;

    unsigned short errors;
    unsigned char  sample_number;
    unsigned short packege_number;
} package_data_t;



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
 * */

#define ERR_NONE               0x0000
#define ERR_AT_RESPONSE        0x0001

#define ERR_NETWORK_FAIL       0x0002
#define ERR_HTTP_FAIL          0x0004

#define ERR_GPS_FAIL           0x0008

#define ERR_TEMP_SENSOR        0x0010
#define ERR_IMU_FAIL           0x0020
// ... add as needed


void init_package_data(void);

package_data_t* write_package_data();

package_data_t* read_package_data();

int package_data_add_error(unsigned short error);

int package_data_set_sample_number(unsigned char sample_n);

int package_data_set_packege_number(unsigned short packege_number);

int package_data_set_coordinates();

int package_data_set_time();

int package_data_set_temp();

int package_data_set_imu();



void update_package_data();


#endif /* PROJECT_TASK_BEHAVIOR_PACKAGE_H_ */
