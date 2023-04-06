#include "hardware/WS2812B_LED.h"
#include <stdio.h>
#include <stm32f0xx.h>
#include <stm32f091xc.h>
#include <stm32f0xx_hal_dma.h>
#include <stm32f0xx_hal_rcc.h>
#include <stm32f0xx_hal_gpio.h>
#include <string.h>
#include "hardware/STM32.h"

#include "hardware/TFT_LCD_legacy.h"
#include "hardware/TFT_LCD.h"

// data currently being sent from dma to tim3->ccr1
uint16_t ws_io_buffer[WS_BUFFER_SIZE] = {0};


/////////////////////////////////////////////////
// temp buffer for testing
// storage for all the queue elements
//WS_RgbData ws_queue_elements[WS_LED_COUNT * WS_QUEUE_SIZE];

// queue for data to be sent to the ws_io_buffer
//WS_LED_QueueStruct ws_io_queue[WS_LED_COUNT];


/* * * * * * * * * * *
 * WS queue functions*
 * * * * * * * * * * */

// functions for handling the led queue
/*
int is_ws_queue_empty(int led_num) {
	WS_LED_QueueStruct q = ws_io_queue[led_num];
	return q.size == 0;
}

int is_ws_queue_full(int led_num) {
	WS_LED_QueueStruct q = ws_io_queue[led_num];
	return q.size == q.max_size;
}

WS_RgbData* pop_from_ws_queue(int led_num) {
	if(is_ws_queue_empty(led_num)) {
		return (WS_RgbData*)0x0;
	}

	WS_LED_QueueStruct* q = &ws_io_queue[led_num];
	WS_RgbData* d = &q->data[q->tail];
	q->tail = (q->tail + 1) % q->max_size;
	q->size--;
	return d;
}

int add_to_ws_queue(int led_num, uint8_t r, uint8_t g, uint8_t b) {
	if(is_ws_queue_full(led_num)) {
		return 1;
	}
	WS_LED_QueueStruct* q = &ws_io_queue[led_num];
	q->data[q->head].r = r;
	q->data[q->head].g = g;
	q->data[q->head].b = b;
	q->head = (q->head + 1) % q->max_size;
	q->size++;
	return 0;
}

void init_ws_led_queue() {
	for(int i = 0; i < WS_LED_COUNT; i++) {
		for(int j = 0; j < WS_QUEUE_SIZE; j++) {
			ws_queue_elements[(i * WS_LED_COUNT) + j].r = 0;
			ws_queue_elements[(i * WS_LED_COUNT) + j].g = 0;
			ws_queue_elements[(i * WS_LED_COUNT) + j].b = 0;
		}
		ws_io_queue->data = &ws_queue_elements[i * WS_QUEUE_SIZE];
		ws_io_queue->size = 0;
		ws_io_queue->max_size = WS_QUEUE_SIZE;
		ws_io_queue->head = 0;
		ws_io_queue->tail = 0;
	}
}

int ws_insert_queue(int led_num, uint8_t r, uint8_t g, uint8_t b) {
	// insert the color sequence into the selected led's queue
	WS_LED_QueueStruct* q = &ws_io_queue[led_num];
	if(q->size + 3 > q->max_size) { // if queue doesn't have 3 open slots
		return -1; // failed to write to queue
	}
	add_to_ws_queue(led_num, r, g, b);
	return 0;
}


*/

void write_ws_io_buffer(uint16_t* IObuffer, uint32_t index, uint8_t data) {
	// index: items in buffer are grouped in groups of 8 (8 bits to represent values from 0 to 255)
	// 3 items are used to represent each LED
	// after every 3 items in the buffer there are 60 0s for the reset signal
	// so IObuffer[index * 8] is the start of the index'th buffer
	for(int i = 0; i < 8; i++) {
		// (1 << ((8-1) - i)): get the ith bit from the end of the data
		IObuffer[(index * 8) + i] = data & (1 << ((8-1) - i)) ? LOGIC1 : LOGIC0;

//		IObuffer[(index * 8) + ((uint32_t)(index / 8) * RESET_SIZE) + i] = data & (1 << ((8-1) - i)) ? LOGIC1 : LOGIC0;
	}
}

void clear_ws_io_buffer(uint16_t* IObuffer, uint32_t index) {
	// index: items in buffer are grouped in groups of 8 (8 bits to represent values from 0 to 255)
	// so IObuffer[index * 8] is the start of the index'th buffer
	// clears the buffer for led reset
	for(int i = 0; i < 8; i++) {
		IObuffer[(index * 8) + i] = 0;
	}
}

void set_ws_led_io_buffer(uint16_t* IObuffer, uint32_t led_num, uint8_t r, uint8_t g, uint8_t b) {

	write_ws_io_buffer(IObuffer, (led_num * 3) + 0, g);
	write_ws_io_buffer(IObuffer, (led_num * 3) + 1, r);
	write_ws_io_buffer(IObuffer, (led_num * 3) + 2, b);
}

void clear_ws_led_io_buffer(uint16_t* IObuffer, uint32_t led_num) {

	clear_ws_io_buffer(IObuffer, (led_num * 3) + 0);
	clear_ws_io_buffer(IObuffer, (led_num * 3) + 1);
	clear_ws_io_buffer(IObuffer, (led_num * 3) + 2);
}


void init_ws2812b_leds() {
//	init_ws_led_queue();
	init_tft_lcd();
	set_ws_led_io_buffer(ws_io_buffer, 0, 0xFF, 0x00, 0xff);
	display_buff();


	init_pb4();
	init_tim3((uint32_t)&ws_io_buffer);
	init_dma1_ch3((uint32_t)&ws_io_buffer, WS_BUFFER_SIZE, (uint32_t)&TIM3->CCR1);

	ws_enable_led_update();
}


void ws_update_buffer() {
	// to be used by the dma transfer complete interrupt handler
	// updates the buffer with the next value in the queue or sets the
	// buffer to 0 if leds are currently being reset.
	// For each led: If the queue is empty and not being reset, don't touch the buffer value. Else, update it

	// for each led:
	// check if it should be updated
	// check queue length
	// if queue.size > 0 get next in queue
	// update buffer
	// else do nothing
	for (int i = 0; i < WS_LED_COUNT; i++) {

	}

}

void ws_enable_led_update() {
	DMA1_Channel3->CCR |= DMA_CCR_EN;
}
void ws_disable_led_update() {
	while(DMA1_Channel3->CNDTR); // wait for channel to finish any ongoing transfers
	DMA1_Channel3->CCR &= ~DMA_CCR_EN;
}

void display_buff(void) {
	char num_str[10];
	for (int i = 0; i < 8; i++) {
		itoa(ws_io_buffer[i], num_str, 10);
		LCD_DrawString(20, 20 * (i+1), BLACK, WHITE, num_str, 16, 0);

	}
	for (int i = 0; i < 8; i++) {
		itoa(ws_io_buffer[i+8], num_str, 10);
		LCD_DrawString(20+25, 20 * (i+1), BLACK, WHITE, num_str, 16, 0);

	}
	for (int i = 0; i < 8; i++) {
		itoa(ws_io_buffer[i+16], num_str, 10);
		LCD_DrawString(20+50, 20 * (i+1), BLACK, WHITE, num_str, 16, 0);

	}
}
