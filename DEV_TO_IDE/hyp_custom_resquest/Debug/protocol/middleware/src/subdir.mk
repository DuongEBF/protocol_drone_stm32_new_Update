################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../protocol/middleware/src/canard.c \
../protocol/middleware/src/hyp.msg.BatteryStatus_Hyp.c \
../protocol/middleware/src/hyp.msg.GetNodeInfor_Hyp_req.c \
../protocol/middleware/src/hyp.msg.GetNodeInfor_Hyp_res.c \
../protocol/middleware/src/hyp.msg.HeartBeat_Hyp.c 

OBJS += \
./protocol/middleware/src/canard.o \
./protocol/middleware/src/hyp.msg.BatteryStatus_Hyp.o \
./protocol/middleware/src/hyp.msg.GetNodeInfor_Hyp_req.o \
./protocol/middleware/src/hyp.msg.GetNodeInfor_Hyp_res.o \
./protocol/middleware/src/hyp.msg.HeartBeat_Hyp.o 

C_DEPS += \
./protocol/middleware/src/canard.d \
./protocol/middleware/src/hyp.msg.BatteryStatus_Hyp.d \
./protocol/middleware/src/hyp.msg.GetNodeInfor_Hyp_req.d \
./protocol/middleware/src/hyp.msg.GetNodeInfor_Hyp_res.d \
./protocol/middleware/src/hyp.msg.HeartBeat_Hyp.d 


# Each subdirectory must supply rules for building sources it contributes
protocol/middleware/src/%.o protocol/middleware/src/%.su protocol/middleware/src/%.cyclo: ../protocol/middleware/src/%.c protocol/middleware/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/duong/Du_an/HYPMOTION/DEV_TO_IDE/hyp_custom_resquest/protocol/hardware/include" -I"/home/duong/Du_an/HYPMOTION/DEV_TO_IDE/hyp_custom_resquest/protocol/middleware/include" -O0 -ffunction-sections -fdata-sections -Wall -DCANARD_ENABLE_CUSTOM_BUILD_CONFIG=1 -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-protocol-2f-middleware-2f-src

clean-protocol-2f-middleware-2f-src:
	-$(RM) ./protocol/middleware/src/canard.cyclo ./protocol/middleware/src/canard.d ./protocol/middleware/src/canard.o ./protocol/middleware/src/canard.su ./protocol/middleware/src/hyp.msg.BatteryStatus_Hyp.cyclo ./protocol/middleware/src/hyp.msg.BatteryStatus_Hyp.d ./protocol/middleware/src/hyp.msg.BatteryStatus_Hyp.o ./protocol/middleware/src/hyp.msg.BatteryStatus_Hyp.su ./protocol/middleware/src/hyp.msg.GetNodeInfor_Hyp_req.cyclo ./protocol/middleware/src/hyp.msg.GetNodeInfor_Hyp_req.d ./protocol/middleware/src/hyp.msg.GetNodeInfor_Hyp_req.o ./protocol/middleware/src/hyp.msg.GetNodeInfor_Hyp_req.su ./protocol/middleware/src/hyp.msg.GetNodeInfor_Hyp_res.cyclo ./protocol/middleware/src/hyp.msg.GetNodeInfor_Hyp_res.d ./protocol/middleware/src/hyp.msg.GetNodeInfor_Hyp_res.o ./protocol/middleware/src/hyp.msg.GetNodeInfor_Hyp_res.su ./protocol/middleware/src/hyp.msg.HeartBeat_Hyp.cyclo ./protocol/middleware/src/hyp.msg.HeartBeat_Hyp.d ./protocol/middleware/src/hyp.msg.HeartBeat_Hyp.o ./protocol/middleware/src/hyp.msg.HeartBeat_Hyp.su

.PHONY: clean-protocol-2f-middleware-2f-src

