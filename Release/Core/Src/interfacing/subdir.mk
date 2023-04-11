################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/interfacing/buttons.c \
../Core/Src/interfacing/leds.c \
../Core/Src/interfacing/scoreboard.c 

C_DEPS += \
./Core/Src/interfacing/buttons.d \
./Core/Src/interfacing/leds.d \
./Core/Src/interfacing/scoreboard.d 

OBJS += \
./Core/Src/interfacing/buttons.o \
./Core/Src/interfacing/leds.o \
./Core/Src/interfacing/scoreboard.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/interfacing/%.o Core/Src/interfacing/%.su: ../Core/Src/interfacing/%.c Core/Src/interfacing/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F091xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-interfacing

clean-Core-2f-Src-2f-interfacing:
	-$(RM) ./Core/Src/interfacing/buttons.d ./Core/Src/interfacing/buttons.o ./Core/Src/interfacing/buttons.su ./Core/Src/interfacing/leds.d ./Core/Src/interfacing/leds.o ./Core/Src/interfacing/leds.su ./Core/Src/interfacing/scoreboard.d ./Core/Src/interfacing/scoreboard.o ./Core/Src/interfacing/scoreboard.su

.PHONY: clean-Core-2f-Src-2f-interfacing

