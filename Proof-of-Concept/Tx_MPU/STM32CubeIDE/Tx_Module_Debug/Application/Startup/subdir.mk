################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Application/Startup/gcc_setup.s \
../Application/Startup/txm_module_preamble.s 

OBJS += \
./Application/Startup/gcc_setup.o \
./Application/Startup/txm_module_preamble.o 

S_DEPS += \
./Application/Startup/gcc_setup.d \
./Application/Startup/txm_module_preamble.d 


# Each subdirectory must supply rules for building sources it contributes
Application/Startup/%.o: ../Application/Startup/%.s Application/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m33 -g3 -DDEBUG -DTX_SINGLE_MODE_NON_SECURE=1 -c -fpie -fno-plt -mpic-data-is-text-relative -msingle-pic-base -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Application-2f-Startup

clean-Application-2f-Startup:
	-$(RM) ./Application/Startup/gcc_setup.d ./Application/Startup/gcc_setup.o ./Application/Startup/txm_module_preamble.d ./Application/Startup/txm_module_preamble.o

.PHONY: clean-Application-2f-Startup

