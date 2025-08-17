################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../UART_IRQ/ring_buff.c \
../UART_IRQ/uart_irq.c 

OBJS += \
./UART_IRQ/ring_buff.o \
./UART_IRQ/uart_irq.o 

C_DEPS += \
./UART_IRQ/ring_buff.d \
./UART_IRQ/uart_irq.d 


# Each subdirectory must supply rules for building sources it contributes
UART_IRQ/%.o UART_IRQ/%.su UART_IRQ/%.cyclo: ../UART_IRQ/%.c UART_IRQ/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G0C1xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"/media/duong/DataLinux/Du_an/HYPMOTION/DEV_TO_IDE/SPARROW_BOARD_DIAGRAM_V0_1/MAVLink_Custom/hypmotion_mavlink_custom" -I"/media/duong/DataLinux/Du_an/HYPMOTION/DEV_TO_IDE/SPARROW_BOARD_DIAGRAM_V0_1/UART_IRQ" -I"/media/duong/DataLinux/Du_an/HYPMOTION/DEV_TO_IDE/SPARROW_BOARD_DIAGRAM_V0_1/LED_CONTROL" -I"/media/duong/DataLinux/Du_an/HYPMOTION/DEV_TO_IDE/SPARROW_BOARD_DIAGRAM_V0_1/FAN_CONTROL" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-UART_IRQ

clean-UART_IRQ:
	-$(RM) ./UART_IRQ/ring_buff.cyclo ./UART_IRQ/ring_buff.d ./UART_IRQ/ring_buff.o ./UART_IRQ/ring_buff.su ./UART_IRQ/uart_irq.cyclo ./UART_IRQ/uart_irq.d ./UART_IRQ/uart_irq.o ./UART_IRQ/uart_irq.su

.PHONY: clean-UART_IRQ

