################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../canard/canard.c 

OBJS += \
./canard/canard.o 

C_DEPS += \
./canard/canard.d 


# Each subdirectory must supply rules for building sources it contributes
canard/%.o canard/%.su canard/%.cyclo: ../canard/%.c canard/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"/home/duong/Du_an/HYPMOTION/DEV_TO_IDE/fd_can_hypcustom_respone/canard" -I"/home/duong/Du_an/HYPMOTION/DEV_TO_IDE/fd_can_hypcustom_respone/hyp_generated/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-canard

clean-canard:
	-$(RM) ./canard/canard.cyclo ./canard/canard.d ./canard/canard.o ./canard/canard.su

.PHONY: clean-canard

