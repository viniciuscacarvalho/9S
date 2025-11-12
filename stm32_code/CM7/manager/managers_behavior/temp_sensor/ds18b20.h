#ifndef INC_DS18B20_H_
#define INC_DS18B20_H_

//#include "main.h"
#include "../../manager.h"

float DS18B20_GetTemp(void);
uint8_t DS18B20_Reset(void);
void DS18B20_WriteByte(uint8_t byte);
uint8_t DS18B20_ReadByte(void);

#endif
