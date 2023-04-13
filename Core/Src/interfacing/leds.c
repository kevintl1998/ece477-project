#include "interfacing/leds.h"

#include "stm32f0xx.h"

#include "hardware/ws2812b/WS2812B_LED.h"
#include "hardware/STM32.h"

void init_leds(void) {
	init_ws2812b_leds();
}

void init_led_timer(void) {
	init_tim16();
}
