################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include UART_IRQ/subdir.mk
-include LED_CONTROL/subdir.mk
-include FAN_CONTROL/subdir.mk
-include Drivers/STM32G0xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := SPARROW_BOARD_DIAGRAM_V0_1
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
SPARROW_BOARD_DIAGRAM_V0_1.elf \

MAP_FILES += \
SPARROW_BOARD_DIAGRAM_V0_1.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
SPARROW_BOARD_DIAGRAM_V0_1.list \


# All Target
all: main-build

# Main-build Target
main-build: SPARROW_BOARD_DIAGRAM_V0_1.elf secondary-outputs

# Tool invocations
SPARROW_BOARD_DIAGRAM_V0_1.elf SPARROW_BOARD_DIAGRAM_V0_1.map: $(OBJS) $(USER_OBJS) /media/duong/DataLinux/Du_an/HYPMOTION/DEV_TO_IDE/SPARROW_BOARD_DIAGRAM_V0_1/STM32G0C1CEUX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "SPARROW_BOARD_DIAGRAM_V0_1.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0plus -T"/media/duong/DataLinux/Du_an/HYPMOTION/DEV_TO_IDE/SPARROW_BOARD_DIAGRAM_V0_1/STM32G0C1CEUX_FLASH.ld" --specs=nosys.specs -Wl,-Map="SPARROW_BOARD_DIAGRAM_V0_1.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

SPARROW_BOARD_DIAGRAM_V0_1.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "SPARROW_BOARD_DIAGRAM_V0_1.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) SPARROW_BOARD_DIAGRAM_V0_1.elf SPARROW_BOARD_DIAGRAM_V0_1.list SPARROW_BOARD_DIAGRAM_V0_1.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
