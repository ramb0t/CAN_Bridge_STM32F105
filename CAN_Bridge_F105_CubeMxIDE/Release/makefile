################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
CAN_Bridge_F105_CubeMx.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
CAN_Bridge_F105_CubeMx.list \

OBJCOPY_BIN += \
CAN_Bridge_F105_CubeMx.bin \


# All Target
all: CAN_Bridge_F105_CubeMx.elf secondary-outputs

# Tool invocations
CAN_Bridge_F105_CubeMx.elf: $(OBJS) $(USER_OBJS) C:\Users\robth\Documents\Git\CAN_Bridge_STM32F105\CAN_Bridge_F105_CubeMxIDE\STM32F105RCTX_FLASH.ld
	arm-none-eabi-gcc -o "CAN_Bridge_F105_CubeMx.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\robth\Documents\Git\CAN_Bridge_STM32F105\CAN_Bridge_F105_CubeMxIDE\STM32F105RCTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="CAN_Bridge_F105_CubeMx.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

CAN_Bridge_F105_CubeMx.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "CAN_Bridge_F105_CubeMx.list"
	@echo 'Finished building: $@'
	@echo ' '

CAN_Bridge_F105_CubeMx.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "CAN_Bridge_F105_CubeMx.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
