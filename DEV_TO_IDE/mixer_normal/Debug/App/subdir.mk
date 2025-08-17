################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/command_excute.c \
../App/mixer.c \
../App/uart.c 

OBJS += \
./App/command_excute.o \
./App/mixer.o \
./App/uart.o 

C_DEPS += \
./App/command_excute.d \
./App/mixer.d \
./App/uart.d 


# Each subdirectory must supply rules for building sources it contributes
App/%.o App/%.su App/%.cyclo: ../App/%.c App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/duong/Du_an/HYPMOTION/DEV_TO_IDE/mixer_normal/App" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-App

clean-App:
	-$(RM) ./App/command_excute.cyclo ./App/command_excute.d ./App/command_excute.o ./App/command_excute.su ./App/mixer.cyclo ./App/mixer.d ./App/mixer.o ./App/mixer.su ./App/uart.cyclo ./App/uart.d ./App/uart.o ./App/uart.su

.PHONY: clean-App

