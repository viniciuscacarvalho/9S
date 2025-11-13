/*
 * package.c
 *
 *  Created on: May 1, 2025
 *      Author: viny
 */

#include "package.h"

package_data_t package_data[2];
char package_data_index = 0;


void init_package_data(void)
{
	package_data[0].packege_number = 0;
	package_data[1].packege_number = 0;
}

package_data_t* write_package_data()
{
    return &package_data[package_data_index];
}


package_data_t* read_package_data()
{
    return &package_data[!package_data_index];
}

int package_data_add_error(unsigned short error)
{
	package_data[package_data_index].errors |= error;
}



void update_package_data()
{
	package_data[package_data_index].packege_number++;
    package_data_index = !package_data_index;
    package_data[package_data_index].packege_number++;
}
