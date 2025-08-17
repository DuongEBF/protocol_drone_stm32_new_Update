################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LIB/canard/canard.c 

OBJS += \
./LIB/canard/canard.o 

C_DEPS += \
./LIB/canard/canard.d 


# Each subdirectory must supply rules for building sources it contributes
LIB/canard/%.o LIB/canard/%.su LIB/canard/%.cyclo: ../LIB/canard/%.c LIB/canard/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/duong/Du_an/HYPMOTION/DEV_TO_IDE/debug_heartbeat_ide/LIB/canard" -I"/home/duong/Du_an/HYPMOTION/DEV_TO_IDE/debug_heartbeat_ide/LIB/Lib_canard_func/include" -I"/home/duong/Du_an/HYPMOTION/DEV_TO_IDE/debug_heartbeat_ide/LIB/hyp_generated/include" -O0 -ffunction-sections -fdata-sections -Wall -DCANARD_ENABLE_CUSTOM_BUILD_CONFIG=1 -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-LIB-2f-canard

clean-LIB-2f-canard:
	-$(RM) ./LIB/canard/canard.cyclo ./LIB/canard/canard.d ./LIB/canard/canard.o ./LIB/canard/canard.su

.PHONY: clean-LIB-2f-canard

