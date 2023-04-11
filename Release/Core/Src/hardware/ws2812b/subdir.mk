################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/hardware/ws2812b/WS2812B_LED.c \
../Core/Src/hardware/ws2812b/WS2812B_led_queue.c 

C_DEPS += \
./Core/Src/hardware/ws2812b/WS2812B_LED.d \
./Core/Src/hardware/ws2812b/WS2812B_led_queue.d 

OBJS += \
./Core/Src/hardware/ws2812b/WS2812B_LED.o \
./Core/Src/hardware/ws2812b/WS2812B_led_queue.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/hardware/ws2812b/%.o Core/Src/hardware/ws2812b/%.su: ../Core/Src/hardware/ws2812b/%.c Core/Src/hardware/ws2812b/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F091xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-hardware-2f-ws2812b

clean-Core-2f-Src-2f-hardware-2f-ws2812b:
	-$(RM) ./Core/Src/hardware/ws2812b/WS2812B_LED.d ./Core/Src/hardware/ws2812b/WS2812B_LED.o ./Core/Src/hardware/ws2812b/WS2812B_LED.su ./Core/Src/hardware/ws2812b/WS2812B_led_queue.d ./Core/Src/hardware/ws2812b/WS2812B_led_queue.o ./Core/Src/hardware/ws2812b/WS2812B_led_queue.su

.PHONY: clean-Core-2f-Src-2f-hardware-2f-ws2812b

