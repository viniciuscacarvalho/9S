################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../one_wire/ds18b20.c \
../one_wire/ow.c 

OBJS += \
./one_wire/ds18b20.o \
./one_wire/ow.o 

C_DEPS += \
./one_wire/ds18b20.d \
./one_wire/ow.d 


# Each subdirectory must supply rules for building sources it contributes
one_wire/%.o one_wire/%.su one_wire/%.cyclo: ../one_wire/%.c one_wire/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H755xx -DUSE_PWR_DIRECT_SMPS_SUPPLY -c -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FatFs/src -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-one_wire

clean-one_wire:
	-$(RM) ./one_wire/ds18b20.cyclo ./one_wire/ds18b20.d ./one_wire/ds18b20.o ./one_wire/ds18b20.su ./one_wire/ow.cyclo ./one_wire/ow.d ./one_wire/ow.o ./one_wire/ow.su

.PHONY: clean-one_wire

