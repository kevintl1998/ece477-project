################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/hardware/STM32.c \
../Core/Src/hardware/TFT_LCD_legacy.c 

C_DEPS += \
./Core/Src/hardware/STM32.d \
./Core/Src/hardware/TFT_LCD_legacy.d 

OBJS += \
./Core/Src/hardware/STM32.o \
./Core/Src/hardware/TFT_LCD_legacy.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/hardware/%.o Core/Src/hardware/%.su: ../Core/Src/hardware/%.c Core/Src/hardware/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F091xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-hardware

clean-Core-2f-Src-2f-hardware:
	-$(RM) ./Core/Src/hardware/STM32.d ./Core/Src/hardware/STM32.o ./Core/Src/hardware/STM32.su ./Core/Src/hardware/TFT_LCD_legacy.d ./Core/Src/hardware/TFT_LCD_legacy.o ./Core/Src/hardware/TFT_LCD_legacy.su

.PHONY: clean-Core-2f-Src-2f-hardware

