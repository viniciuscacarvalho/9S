################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../manager/managers_behavior/battery_behavior.c \
../manager/managers_behavior/cnss_behavior.c \
../manager/managers_behavior/imu_behavior.c \
../manager/managers_behavior/nb_iot_behavior.c \
../manager/managers_behavior/sd_card_behavior.c \
../manager/managers_behavior/temperature_behavior.c 

OBJS += \
./manager/managers_behavior/battery_behavior.o \
./manager/managers_behavior/cnss_behavior.o \
./manager/managers_behavior/imu_behavior.o \
./manager/managers_behavior/nb_iot_behavior.o \
./manager/managers_behavior/sd_card_behavior.o \
./manager/managers_behavior/temperature_behavior.o 

C_DEPS += \
./manager/managers_behavior/battery_behavior.d \
./manager/managers_behavior/cnss_behavior.d \
./manager/managers_behavior/imu_behavior.d \
./manager/managers_behavior/nb_iot_behavior.d \
./manager/managers_behavior/sd_card_behavior.d \
./manager/managers_behavior/temperature_behavior.d 


# Each subdirectory must supply rules for building sources it contributes
manager/managers_behavior/%.o manager/managers_behavior/%.su manager/managers_behavior/%.cyclo: ../manager/managers_behavior/%.c manager/managers_behavior/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H755xx -DUSE_PWR_DIRECT_SMPS_SUPPLY -c -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FatFs/src -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-manager-2f-managers_behavior

clean-manager-2f-managers_behavior:
	-$(RM) ./manager/managers_behavior/battery_behavior.cyclo ./manager/managers_behavior/battery_behavior.d ./manager/managers_behavior/battery_behavior.o ./manager/managers_behavior/battery_behavior.su ./manager/managers_behavior/cnss_behavior.cyclo ./manager/managers_behavior/cnss_behavior.d ./manager/managers_behavior/cnss_behavior.o ./manager/managers_behavior/cnss_behavior.su ./manager/managers_behavior/imu_behavior.cyclo ./manager/managers_behavior/imu_behavior.d ./manager/managers_behavior/imu_behavior.o ./manager/managers_behavior/imu_behavior.su ./manager/managers_behavior/nb_iot_behavior.cyclo ./manager/managers_behavior/nb_iot_behavior.d ./manager/managers_behavior/nb_iot_behavior.o ./manager/managers_behavior/nb_iot_behavior.su ./manager/managers_behavior/sd_card_behavior.cyclo ./manager/managers_behavior/sd_card_behavior.d ./manager/managers_behavior/sd_card_behavior.o ./manager/managers_behavior/sd_card_behavior.su ./manager/managers_behavior/temperature_behavior.cyclo ./manager/managers_behavior/temperature_behavior.d ./manager/managers_behavior/temperature_behavior.o ./manager/managers_behavior/temperature_behavior.su

.PHONY: clean-manager-2f-managers_behavior

