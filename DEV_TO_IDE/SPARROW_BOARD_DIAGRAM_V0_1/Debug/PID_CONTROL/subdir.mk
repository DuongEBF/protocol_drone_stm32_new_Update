################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../PID_CONTROL/mavlink_from_tobufi.c \
../PID_CONTROL/pid_controller.c 

OBJS += \
./PID_CONTROL/mavlink_from_tobufi.o \
./PID_CONTROL/pid_controller.o 

C_DEPS += \
./PID_CONTROL/mavlink_from_tobufi.d \
./PID_CONTROL/pid_controller.d 


# Each subdirectory must supply rules for building sources it contributes
PID_CONTROL/%.o PID_CONTROL/%.su PID_CONTROL/%.cyclo: ../PID_CONTROL/%.c PID_CONTROL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G0C1xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"/media/duong/DataLinux/Du_an/HYPMOTION/DEV_TO_IDE/SPARROW_BOARD_DIAGRAM_V0_1/MAVLink_Custom/hypmotion_mavlink_custom" -I"/media/duong/DataLinux/Du_an/HYPMOTION/DEV_TO_IDE/SPARROW_BOARD_DIAGRAM_V0_1/UART_IRQ" -I"/media/duong/DataLinux/Du_an/HYPMOTION/DEV_TO_IDE/SPARROW_BOARD_DIAGRAM_V0_1/PID_CONTROL" -I"/media/duong/DataLinux/Du_an/HYPMOTION/DEV_TO_IDE/SPARROW_BOARD_DIAGRAM_V0_1/LED_CONTROL" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-PID_CONTROL

clean-PID_CONTROL:
	-$(RM) ./PID_CONTROL/mavlink_from_tobufi.cyclo ./PID_CONTROL/mavlink_from_tobufi.d ./PID_CONTROL/mavlink_from_tobufi.o ./PID_CONTROL/mavlink_from_tobufi.su ./PID_CONTROL/pid_controller.cyclo ./PID_CONTROL/pid_controller.d ./PID_CONTROL/pid_controller.o ./PID_CONTROL/pid_controller.su

.PHONY: clean-PID_CONTROL

