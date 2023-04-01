#ifndef WS2812B_LED
#define WS2812B_LED


#include <stdint.h>

#define LOGIC1 40
#define LOGIC0 20

#define LED_DATA_SIZE 24
#define WS_LED_COUNT 1

// buffer size to contain all the bits currently being sent to the LEDs
#define WS_BUFFER_SIZE (LED_DATA_SIZE * WS_LED_COUNT)

// size of the queue for each led. can store up to 10 colors in each led queue
#define WS_QUEUE_SIZE 10

typedef struct WS_RgbData {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} WS_RgbData;

typedef struct WS_LED_QueueStruct {
	WS_RgbData* data;
	uint32_t size;
	uint32_t max_size;
	uint32_t head;
	uint32_t tail;
} WS_LED_QueueStruct;

// stores the number of DMA cycles that CCR1 needs to be set to 0 for
#define WS_RESET_LENGTH 40;
extern uint8_t ws_reset_state[];

//extern uint32_t num[];
extern uint16_t ws_io_buffer[];
extern WS_LED_QueueStruct ws_io_queue[];

void set_ws_led_io_buffer(uint16_t* IObuffer, uint32_t led_num, uint8_t r, uint8_t g, uint8_t b);
void clear_ws_led_io_buffer(uint16_t* IObuffer, uint32_t led_num);

// initializes everything related to the ws2812b leds
void init_ws2812b_leds();
//void ws2812_write(uint32_t i, char*);
//void ws2812_write(uint32_t i, char r, char g, char b);
//void set_ws_led_io_buffer(uint16_t* IObuffer, uint32_t led_num, uint8_t r, uint8_t g, uint8_t b);
void ws_update_buffer();
int ws_insert_queue(int led_num, uint8_t r, uint8_t g, uint8_t b);
void ws_reset_led(int led_num);

void ws_enable_led_update();
void ws_disable_led_update();

void display_buff();

#endif
