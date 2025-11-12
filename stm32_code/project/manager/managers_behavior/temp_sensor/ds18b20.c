//#include "main.h"
#include "ds18b20.h"
#include "delay.h"  // Custom microsecond delay using DWT or TIM

#define DS18B20_PORT GPIOC
#define DS18B20_PIN GPIO_PIN_0

void DS18B20_Pin_Output(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DS18B20_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(DS18B20_PORT, &GPIO_InitStruct);
}

void DS18B20_Pin_Input(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DS18B20_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(DS18B20_PORT, &GPIO_InitStruct);
}

uint8_t DS18B20_Reset(void) {
    uint8_t response = 0;
    DS18B20_Pin_Output();
    HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_RESET);
    Delay_us(480);
    DS18B20_Pin_Input();
    Delay_us(80);
    if (!HAL_GPIO_ReadPin(DS18B20_PORT, DS18B20_PIN)) response = 1;
    Delay_us(400);
    return response;
}

void DS18B20_WriteBit(uint8_t bit) {
    DS18B20_Pin_Output();
    HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_RESET);
    Delay_us(bit ? 1 : 60);
    DS18B20_Pin_Input();
    Delay_us(bit ? 60 : 1);
}

uint8_t DS18B20_ReadBit(void) {
    uint8_t bit = 0;
    DS18B20_Pin_Output();
    HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_RESET);
    Delay_us(2);
    DS18B20_Pin_Input();
    Delay_us(10);
    bit = HAL_GPIO_ReadPin(DS18B20_PORT, DS18B20_PIN);
    Delay_us(50);
    return bit;
}

void DS18B20_WriteByte(uint8_t byte) {
    for (int i = 0; i < 8; i++) {
        DS18B20_WriteBit(byte & (1 << i));
    }
}

uint8_t DS18B20_ReadByte(void) {
    uint8_t byte = 0;
    for (int i = 0; i < 8; i++) {
        if (DS18B20_ReadBit()) byte |= 1 << i;
    }
    return byte;
}

float DS18B20_GetTemp(void) {
    uint8_t temp_lsb, temp_msb;
    int16_t temp_raw;

    DS18B20_Reset();
    DS18B20_WriteByte(0xCC);  // Skip ROM
    DS18B20_WriteByte(0x44);  // Convert T
    HAL_Delay(750);           // Wait conversion

    DS18B20_Reset();
    DS18B20_WriteByte(0xCC);  // Skip ROM
    DS18B20_WriteByte(0xBE);  // Read Scratchpad

    temp_lsb = DS18B20_ReadByte();
    temp_msb = DS18B20_ReadByte();

    temp_raw = (temp_msb << 8) | temp_lsb;
    return (float)temp_raw / 16.0;
}
