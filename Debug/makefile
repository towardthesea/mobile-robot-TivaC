################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: test_motor_driver.elf

# Tool invocations
test_motor_driver.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross GCC Linker'
	arm-none-eabi-gcc -static -L/home/pnguyen/TivaC/gcc-arm-none-eabi-5_4-2016q3/lib/gcc/arm-none-eabi/5.4.1 -L/home/pnguyen/TivaC/SW-TM4C-2.1.4.178/sensorlib/gcc -L/home/pnguyen/TivaC/SW-TM4C-2.1.4.178/driverlib/gcc -Wl,--static,--gc-sections,-T../TM4C.ld -mthumb -mcpu=cortex-m4 -o "test_motor_driver.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) test_motor_driver.elf
	-@echo ' '

post-build:
	-@echo 'Generate binary file from elf file'
	-arm-none-eabi-objcopy -O binary test_motor_driver.elf test_motor_driver.bin
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
