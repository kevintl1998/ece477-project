################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/releases/\ entry.c \
../Core/Src/releases/debug.c \
../Core/Src/releases/release.c \
../Core/Src/releases/unit_test.c 

C_DEPS += \
./Core/Src/releases/\ entry.d \
./Core/Src/releases/debug.d \
./Core/Src/releases/release.d \
./Core/Src/releases/unit_test.d 

OBJS += \
./Core/Src/releases/\ entry.o \
./Core/Src/releases/debug.o \
./Core/Src/releases/release.o \
./Core/Src/releases/unit_test.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/releases/\ entry.o: ../Core/Src/releases/\ entry.c Core/Src/releases/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F091xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/releases/ entry.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/releases/%.o Core/Src/releases/%.su: ../Core/Src/releases/%.c Core/Src/releases/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F091xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-releases

clean-Core-2f-Src-2f-releases:
	-$(RM) ./Core/Src/releases/\ entry.d ./Core/Src/releases/\ entry.o ./Core/Src/releases/\ entry.su ./Core/Src/releases/debug.d ./Core/Src/releases/debug.o ./Core/Src/releases/debug.su ./Core/Src/releases/release.d ./Core/Src/releases/release.o ./Core/Src/releases/release.su ./Core/Src/releases/unit_test.d ./Core/Src/releases/unit_test.o ./Core/Src/releases/unit_test.su

.PHONY: clean-Core-2f-Src-2f-releases

