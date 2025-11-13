################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../manager/managers_behavior/temp_sensor/delay.c \
../manager/managers_behavior/temp_sensor/ds18b20.c 

OBJS += \
./manager/managers_behavior/temp_sensor/delay.o \
./manager/managers_behavior/temp_sensor/ds18b20.o 

C_DEPS += \
./manager/managers_behavior/temp_sensor/delay.d \
./manager/managers_behavior/temp_sensor/ds18b20.d 


# Each subdirectory must supply rules for building sources it contributes
manager/managers_behavior/temp_sensor/%.o manager/managers_behavior/temp_sensor/%.su manager/managers_behavior/temp_sensor/%.cyclo: ../manager/managers_behavior/temp_sensor/%.c manager/managers_behavior/temp_sensor/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H755xx -DUSE_PWR_DIRECT_SMPS_SUPPLY -c -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FatFs/src -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-manager-2f-managers_behavior-2f-temp_sensor

clean-manager-2f-managers_behavior-2f-temp_sensor:
	-$(RM) ./manager/managers_behavior/temp_sensor/delay.cyclo ./manager/managers_behavior/temp_sensor/delay.d ./manager/managers_behavior/temp_sensor/delay.o ./manager/managers_behavior/temp_sensor/delay.su ./manager/managers_behavior/temp_sensor/ds18b20.cyclo ./manager/managers_behavior/temp_sensor/ds18b20.d ./manager/managers_behavior/temp_sensor/ds18b20.o ./manager/managers_behavior/temp_sensor/ds18b20.su

.PHONY: clean-manager-2f-managers_behavior-2f-temp_sensor

