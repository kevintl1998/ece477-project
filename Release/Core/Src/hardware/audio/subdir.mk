################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/hardware/audio/midi.c \
../Core/Src/hardware/audio/scale.c \
../Core/Src/hardware/audio/step.c \
../Core/Src/hardware/audio/wavetable.c 

C_DEPS += \
./Core/Src/hardware/audio/midi.d \
./Core/Src/hardware/audio/scale.d \
./Core/Src/hardware/audio/step.d \
./Core/Src/hardware/audio/wavetable.d 

OBJS += \
./Core/Src/hardware/audio/midi.o \
./Core/Src/hardware/audio/scale.o \
./Core/Src/hardware/audio/step.o \
./Core/Src/hardware/audio/wavetable.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/hardware/audio/%.o Core/Src/hardware/audio/%.su: ../Core/Src/hardware/audio/%.c Core/Src/hardware/audio/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F091xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-hardware-2f-audio

clean-Core-2f-Src-2f-hardware-2f-audio:
	-$(RM) ./Core/Src/hardware/audio/midi.d ./Core/Src/hardware/audio/midi.o ./Core/Src/hardware/audio/midi.su ./Core/Src/hardware/audio/scale.d ./Core/Src/hardware/audio/scale.o ./Core/Src/hardware/audio/scale.su ./Core/Src/hardware/audio/step.d ./Core/Src/hardware/audio/step.o ./Core/Src/hardware/audio/step.su ./Core/Src/hardware/audio/wavetable.d ./Core/Src/hardware/audio/wavetable.o ./Core/Src/hardware/audio/wavetable.su

.PHONY: clean-Core-2f-Src-2f-hardware-2f-audio

