#ifndef WS2812B_LED
#define WS2812B_LED

#include <stdint.h>

#include "hardware/ws2812b/WS2812B_led_queue.h"

// logical 1 and 0 represented as pwm values
#define LOGIC1 40
#define LOGIC0 20

// 50 is the minimum, the extra 10 is a just in case
#define RESET_SIZE 55
// # of bits needed to represent a single ws2812 led
#define LED_DATA_SIZE 24
// # of leds in series
#define WS_LED_COUNT 8

// buffer size to contain all the bits currently being sent to the LEDs
#define WS_BUFFER_SIZE ((LED_DATA_SIZE + RESET_SIZE) * WS_LED_COUNT)


#define WS_QUEUE_LENGTH 0


// declared in WS2812B_LED.c
extern uint16_t ws_io_buffer[];
extern WSLED_Queue ws_wait_queue[];

void set_ws_led_io_buffer(uint16_t* IObuffer, uint32_t led_num, uint8_t r, uint8_t g, uint8_t b);
void clear_ws_led_io_buffer(uint16_t* IObuffer, uint32_t led_num);

// initializes everything related to the ws2812b leds
void init_ws2812b_leds();

int add_to_ws_queue(uint32_t led_num, uint8_t r, uint8_t g, uint8_t b, uint32_t hold_cycles);

// function to be called by DMA transmission complete interrupt
void ws_update_buffer();

void display_buff();

#endif
