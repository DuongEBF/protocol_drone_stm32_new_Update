################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cryp_lib/can.c \
../cryp_lib/canard.c \
../cryp_lib/hyp.aes.Encryption_Hyp.c \
../cryp_lib/hyp.msg.BatteryStatus_Hyp.c 

OBJS += \
./cryp_lib/can.o \
./cryp_lib/canard.o \
./cryp_lib/hyp.aes.Encryption_Hyp.o \
./cryp_lib/hyp.msg.BatteryStatus_Hyp.o 

C_DEPS += \
./cryp_lib/can.d \
./cryp_lib/canard.d \
./cryp_lib/hyp.aes.Encryption_Hyp.d \
./cryp_lib/hyp.msg.BatteryStatus_Hyp.d 


# Each subdirectory must supply rules for building sources it contributes
cryp_lib/%.o cryp_lib/%.su cryp_lib/%.cyclo: ../cryp_lib/%.c cryp_lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"/media/duong/DataLinux/Du_an/HYPMOTION/DEV_TO_IDE/AES_recv_batt/tiny_lib" -I"/media/duong/DataLinux/Du_an/HYPMOTION/DEV_TO_IDE/AES_recv_batt/cryp_lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-cryp_lib

clean-cryp_lib:
	-$(RM) ./cryp_lib/can.cyclo ./cryp_lib/can.d ./cryp_lib/can.o ./cryp_lib/can.su ./cryp_lib/canard.cyclo ./cryp_lib/canard.d ./cryp_lib/canard.o ./cryp_lib/canard.su ./cryp_lib/hyp.aes.Encryption_Hyp.cyclo ./cryp_lib/hyp.aes.Encryption_Hyp.d ./cryp_lib/hyp.aes.Encryption_Hyp.o ./cryp_lib/hyp.aes.Encryption_Hyp.su ./cryp_lib/hyp.msg.BatteryStatus_Hyp.cyclo ./cryp_lib/hyp.msg.BatteryStatus_Hyp.d ./cryp_lib/hyp.msg.BatteryStatus_Hyp.o ./cryp_lib/hyp.msg.BatteryStatus_Hyp.su

.PHONY: clean-cryp_lib

