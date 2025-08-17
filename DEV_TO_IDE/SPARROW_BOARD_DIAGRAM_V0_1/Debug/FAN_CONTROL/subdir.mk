################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FAN_CONTROL/fan_controller.c \
../FAN_CONTROL/mavlink_from_tobufi.c 

OBJS += \
./FAN_CONTROL/fan_controller.o \
./FAN_CONTROL/mavlink_from_tobufi.o 

C_DEPS += \
./FAN_CONTROL/fan_controller.d \
./FAN_CONTROL/mavlink_from_tobufi.d 


# Each subdirectory must supply rules for building sources it contributes
FAN_CONTROL/%.o FAN_CONTROL/%.su FAN_CONTROL/%.cyclo: ../FAN_CONTROL/%.c FAN_CONTROL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G0C1xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"/media/duong/DataLinux/Du_an/HYPMOTION/DEV_TO_IDE/SPARROW_BOARD_DIAGRAM_V0_1/MAVLink_Custom/hypmotion_mavlink_custom" -I"/media/duong/DataLinux/Du_an/HYPMOTION/DEV_TO_IDE/SPARROW_BOARD_DIAGRAM_V0_1/UART_IRQ" -I"/media/duong/DataLinux/Du_an/HYPMOTION/DEV_TO_IDE/SPARROW_BOARD_DIAGRAM_V0_1/LED_CONTROL" -I"/media/duong/DataLinux/Du_an/HYPMOTION/DEV_TO_IDE/SPARROW_BOARD_DIAGRAM_V0_1/FAN_CONTROL" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-FAN_CONTROL

clean-FAN_CONTROL:
	-$(RM) ./FAN_CONTROL/fan_controller.cyclo ./FAN_CONTROL/fan_controller.d ./FAN_CONTROL/fan_controller.o ./FAN_CONTROL/fan_controller.su ./FAN_CONTROL/mavlink_from_tobufi.cyclo ./FAN_CONTROL/mavlink_from_tobufi.d ./FAN_CONTROL/mavlink_from_tobufi.o ./FAN_CONTROL/mavlink_from_tobufi.su

.PHONY: clean-FAN_CONTROL

