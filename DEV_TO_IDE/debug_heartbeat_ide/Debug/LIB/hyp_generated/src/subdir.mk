################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LIB/hyp_generated/src/hyp.msgs.BatteryStatus.c 

OBJS += \
./LIB/hyp_generated/src/hyp.msgs.BatteryStatus.o 

C_DEPS += \
./LIB/hyp_generated/src/hyp.msgs.BatteryStatus.d 


# Each subdirectory must supply rules for building sources it contributes
LIB/hyp_generated/src/%.o LIB/hyp_generated/src/%.su LIB/hyp_generated/src/%.cyclo: ../LIB/hyp_generated/src/%.c LIB/hyp_generated/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/duong/Du_an/HYPMOTION/DEV_TO_IDE/debug_heartbeat_ide/LIB/canard" -I"/home/duong/Du_an/HYPMOTION/DEV_TO_IDE/debug_heartbeat_ide/LIB/Lib_canard_func/include" -I"/home/duong/Du_an/HYPMOTION/DEV_TO_IDE/debug_heartbeat_ide/LIB/hyp_generated/include" -O0 -ffunction-sections -fdata-sections -Wall -DCANARD_ENABLE_CUSTOM_BUILD_CONFIG=1 -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-LIB-2f-hyp_generated-2f-src

clean-LIB-2f-hyp_generated-2f-src:
	-$(RM) ./LIB/hyp_generated/src/hyp.msgs.BatteryStatus.cyclo ./LIB/hyp_generated/src/hyp.msgs.BatteryStatus.d ./LIB/hyp_generated/src/hyp.msgs.BatteryStatus.o ./LIB/hyp_generated/src/hyp.msgs.BatteryStatus.su

.PHONY: clean-LIB-2f-hyp_generated-2f-src

