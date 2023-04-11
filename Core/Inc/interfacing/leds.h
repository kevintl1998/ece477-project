#ifndef LEDS_H
#define LEDS_H

#include <stdint.h>

#include "hardware/ws2812b/WS2812B_led_queue.h"

extern int WSLED_QueueAdd(WSLED_Queue* q, uint8_t r, uint8_t g, uint8_t b, uint32_t hold_cycles);

void init_leds();

#endif
