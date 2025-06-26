
#ifndef __COMMAND_CALLBACKS_H__
#define  __COMMAND_CALLBACKS_H__

#include <stdio.h>

void* reset();
void* sample();
void* set_sample_rate(void);
void* calibrate_sensor(void);
void* ping_gnss(void);
void* ping_mc(void);
void* shutdown(void);
void* wakeup(void);
void* version(void);
void* debug(void);

#endif