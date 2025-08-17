################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hyp_generated/src/hyp.msg.BatteryStatus_Hyp.c \
../hyp_generated/src/hyp.msg.GetNodeInfor_Hyp_req.c \
../hyp_generated/src/hyp.msg.GetNodeInfor_Hyp_res.c \
../hyp_generated/src/hyp.msg.HeartBeat_Hyp.c 

OBJS += \
./hyp_generated/src/hyp.msg.BatteryStatus_Hyp.o \
./hyp_generated/src/hyp.msg.GetNodeInfor_Hyp_req.o \
./hyp_generated/src/hyp.msg.GetNodeInfor_Hyp_res.o \
./hyp_generated/src/hyp.msg.HeartBeat_Hyp.o 

C_DEPS += \
./hyp_generated/src/hyp.msg.BatteryStatus_Hyp.d \
./hyp_generated/src/hyp.msg.GetNodeInfor_Hyp_req.d \
./hyp_generated/src/hyp.msg.GetNodeInfor_Hyp_res.d \
./hyp_generated/src/hyp.msg.HeartBeat_Hyp.d 


# Each subdirectory must supply rules for building sources it contributes
hyp_generated/src/%.o hyp_generated/src/%.su hyp_generated/src/%.cyclo: ../hyp_generated/src/%.c hyp_generated/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/duong/Du_an/HYPMOTION/DEV_TO_IDE/hyp_custom_resquest/hyp_generated/include" -I"/home/duong/Du_an/HYPMOTION/DEV_TO_IDE/hyp_custom_resquest/canard" -O0 -ffunction-sections -fdata-sections -Wall -DCANARD_ENABLE_CUSTOM_BUILD_CONFIG=1 -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-hyp_generated-2f-src

clean-hyp_generated-2f-src:
	-$(RM) ./hyp_generated/src/hyp.msg.BatteryStatus_Hyp.cyclo ./hyp_generated/src/hyp.msg.BatteryStatus_Hyp.d ./hyp_generated/src/hyp.msg.BatteryStatus_Hyp.o ./hyp_generated/src/hyp.msg.BatteryStatus_Hyp.su ./hyp_generated/src/hyp.msg.GetNodeInfor_Hyp_req.cyclo ./hyp_generated/src/hyp.msg.GetNodeInfor_Hyp_req.d ./hyp_generated/src/hyp.msg.GetNodeInfor_Hyp_req.o ./hyp_generated/src/hyp.msg.GetNodeInfor_Hyp_req.su ./hyp_generated/src/hyp.msg.GetNodeInfor_Hyp_res.cyclo ./hyp_generated/src/hyp.msg.GetNodeInfor_Hyp_res.d ./hyp_generated/src/hyp.msg.GetNodeInfor_Hyp_res.o ./hyp_generated/src/hyp.msg.GetNodeInfor_Hyp_res.su ./hyp_generated/src/hyp.msg.HeartBeat_Hyp.cyclo ./hyp_generated/src/hyp.msg.HeartBeat_Hyp.d ./hyp_generated/src/hyp.msg.HeartBeat_Hyp.o ./hyp_generated/src/hyp.msg.HeartBeat_Hyp.su

.PHONY: clean-hyp_generated-2f-src

