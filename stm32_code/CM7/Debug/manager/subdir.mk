################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../manager/at_commands_ST87M01.c \
../manager/manager.c \
../manager/package.c 

OBJS += \
./manager/at_commands_ST87M01.o \
./manager/manager.o \
./manager/package.o 

C_DEPS += \
./manager/at_commands_ST87M01.d \
./manager/manager.d \
./manager/package.d 


# Each subdirectory must supply rules for building sources it contributes
manager/%.o manager/%.su manager/%.cyclo: ../manager/%.c manager/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H755xx -DUSE_PWR_DIRECT_SMPS_SUPPLY -c -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FatFs/src -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-manager

clean-manager:
	-$(RM) ./manager/at_commands_ST87M01.cyclo ./manager/at_commands_ST87M01.d ./manager/at_commands_ST87M01.o ./manager/at_commands_ST87M01.su ./manager/manager.cyclo ./manager/manager.d ./manager/manager.o ./manager/manager.su ./manager/package.cyclo ./manager/package.d ./manager/package.o ./manager/package.su

.PHONY: clean-manager

