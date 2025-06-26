#include"command_callbacks.h"

void* reset()            { printf("System reset\n"); }
void* sample()           { printf("Sample command executed\n"); }
void* set_sample_rate()  { printf("Sample rate set\n"); }
void* calibrate_sensor() { printf("Sensor calibrated\n"); }
void* ping_gnss()        { printf("GNSS ping\n"); }
void* ping_mc()          { printf("MCU ping\n"); }
void* shutdown()         { printf("System shutdown\n"); }
void* wakeup()           { printf("System wakeup\n"); }
void* version()          { printf("Firmware version\n"); }
void* debug()            { printf("Debug mode toggled\n"); }
