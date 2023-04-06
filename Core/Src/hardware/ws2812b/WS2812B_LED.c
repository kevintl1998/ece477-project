#include "hardware/ws2812b/WS2812B_LED.h"
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


void write_ws_io_buffer(uint16_t* IObuffer, uint32_t index, uint8_t data) {
	// index: items in buffer are grouped in groups of 8 (8 bits to represent values from 0 to 255)
	// 3 items are used to represent each LED
	// after every 3 items in the buffer there are 60 0s for the reset signal
	// so IObuffer[index * 8] is the start of the index'th buffer
	for(int i = 0; i < 8; i++) {
		// (1 << ((8-1) - i)): get the ith bit from the end of the data
		IObuffer[(index * 8) + i] = data & (1 << ((8-1) - i)) ? LOGIC1 : LOGIC0;
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

	init_tft_lcd();
	display_buff();

	set_ws_led_io_buffer(ws_io_buffer, 0, 0xFF, 0x00, 0xff);

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
