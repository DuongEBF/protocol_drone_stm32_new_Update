################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LIB/queue_struct.c \
../LIB/ring.c \
../LIB/terseCRSF.c 

OBJS += \
./LIB/queue_struct.o \
./LIB/ring.o \
./LIB/terseCRSF.o 

C_DEPS += \
./LIB/queue_struct.d \
./LIB/ring.d \
./LIB/terseCRSF.d 


# Each subdirectory must supply rules for building sources it contributes
LIB/%.o LIB/%.su LIB/%.cyclo: ../LIB/%.c LIB/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/duong/Du_an/HYPMOTION/CRSF_protocol/RX_CRSF_Protocol_IDE/LIB" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-LIB

clean-LIB:
	-$(RM) ./LIB/queue_struct.cyclo ./LIB/queue_struct.d ./LIB/queue_struct.o ./LIB/queue_struct.su ./LIB/ring.cyclo ./LIB/ring.d ./LIB/ring.o ./LIB/ring.su ./LIB/terseCRSF.cyclo ./LIB/terseCRSF.d ./LIB/terseCRSF.o ./LIB/terseCRSF.su

.PHONY: clean-LIB

