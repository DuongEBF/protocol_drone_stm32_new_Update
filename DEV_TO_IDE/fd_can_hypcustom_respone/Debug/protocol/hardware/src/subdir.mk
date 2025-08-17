################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../protocol/hardware/src/can.c 

OBJS += \
./protocol/hardware/src/can.o 

C_DEPS += \
./protocol/hardware/src/can.d 


# Each subdirectory must supply rules for building sources it contributes
protocol/hardware/src/%.o protocol/hardware/src/%.su protocol/hardware/src/%.cyclo: ../protocol/hardware/src/%.c protocol/hardware/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"/home/duong/Du_an/HYPMOTION/DEV_TO_IDE/fd_can_hypcustom_respone/protocol/middleware/inlcude" -I"/home/duong/Du_an/HYPMOTION/DEV_TO_IDE/fd_can_hypcustom_respone/protocol/hardware/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-protocol-2f-hardware-2f-src

clean-protocol-2f-hardware-2f-src:
	-$(RM) ./protocol/hardware/src/can.cyclo ./protocol/hardware/src/can.d ./protocol/hardware/src/can.o ./protocol/hardware/src/can.su

.PHONY: clean-protocol-2f-hardware-2f-src

