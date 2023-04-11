#include "interfacing/leds.h"

#include "stm32f0xx.h"

#include "hardware/ws2812b/WS2812B_LED.h"

void init_leds() {
	init_ws2812b_leds();
}
