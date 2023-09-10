################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/SPI/subdir.mk
-include MCAL/ADC/subdir.mk
-include FreeRTOS/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
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

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
SLAVE.lss \

FLASH_IMAGE += \
SLAVE.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: SLAVE.elf secondary-outputs

# Tool invocations
SLAVE.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,SLAVE.map -mmcu=atmega32 -o "SLAVE.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

SLAVE.lss: SLAVE.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S SLAVE.elf  >"SLAVE.lss"
	@echo 'Finished building: $@'
	@echo ' '

SLAVE.hex: SLAVE.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex SLAVE.elf  "SLAVE.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: SLAVE.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 SLAVE.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) SLAVE.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
