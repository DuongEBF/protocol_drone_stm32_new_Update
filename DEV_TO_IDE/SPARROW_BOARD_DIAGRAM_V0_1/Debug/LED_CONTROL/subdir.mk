################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LED_CONTROL/led_controller.c \
../LED_CONTROL/mavlink_from_FC.c 

OBJS += \
./LED_CONTROL/led_controller.o \
./LED_CONTROL/mavlink_from_FC.o 

C_DEPS += \
./LED_CONTROL/led_controller.d \
./LED_CONTROL/mavlink_from_FC.d 


# Each subdirectory must supply rules for building sources it contributes
LED_CONTROL/%.o LED_CONTROL/%.su LED_CONTROL/%.cyclo: ../LED_CONTROL/%.c LED_CONTROL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G0C1xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"/media/duong/DataLinux/Du_an/HYPMOTION/DEV_TO_IDE/SPARROW_BOARD_DIAGRAM_V0_1/MAVLink_Custom/hypmotion_mavlink_custom" -I"/media/duong/DataLinux/Du_an/HYPMOTION/DEV_TO_IDE/SPARROW_BOARD_DIAGRAM_V0_1/UART_IRQ" -I"/media/duong/DataLinux/Du_an/HYPMOTION/DEV_TO_IDE/SPARROW_BOARD_DIAGRAM_V0_1/LED_CONTROL" -I"/media/duong/DataLinux/Du_an/HYPMOTION/DEV_TO_IDE/SPARROW_BOARD_DIAGRAM_V0_1/FAN_CONTROL" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-LED_CONTROL

clean-LED_CONTROL:
	-$(RM) ./LED_CONTROL/led_controller.cyclo ./LED_CONTROL/led_controller.d ./LED_CONTROL/led_controller.o ./LED_CONTROL/led_controller.su ./LED_CONTROL/mavlink_from_FC.cyclo ./LED_CONTROL/mavlink_from_FC.d ./LED_CONTROL/mavlink_from_FC.o ./LED_CONTROL/mavlink_from_FC.su

.PHONY: clean-LED_CONTROL

