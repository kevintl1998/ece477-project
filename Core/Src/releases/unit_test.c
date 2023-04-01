#include <stdlib.h>
#include <stdint.h>
#include "stm32f0xx.h"
#include <stm32f091xc.h>

#include "releases/unit_test.h"
#include "hardware/TFT_LCD.h"
#include "hardware/TFT_LCD_legacy.h"
#include "hardware/STM32.h"
#include "hardware/WS2812B_LED.h"
#include "util.h"
#include "settings.h"


void test_scoreboard(void);
void test_buttons(void);
void test_solenoid(void);
void test_servo(void);
void test_leds(void);
void test_i2c(void);
void test_audio(void);

/*
 * Consider this the entry point when RELEASE_TYPE in main.c is set to UNIT_TEST
 */
int unit_test(void) {
    /* Every time a function is complete (eg: scoreboard is hooked up to microcontroller,
     * scoreboard functionality is complete, paddle functionality is complete, etc)
     * create a new test here for that function
     */

// Run unit tests for all functions here
    if (DEVICE_ID == PLAYER1) {
        // test functions for p1
    } else if(DEVICE_ID == PLAYER2) {
        // test functions for p2
//    	test_scoreboard();
//    	test_buttons();
//    	test_solenoid();
//    	test_servo();
    	test_leds();
//    	test_i2c();
//    	test_audio();
    }
    return 0;
}

void test_scoreboard(void) {
	init_tft_lcd();

	LCD_DrawRectangle(20, 20, 70, 90, GREEN);


}

void test_buttons(void) {
	init_pc0();
	init_pc1();
	init_tft_lcd();

	uint32_t num = 0;
	char num_str[10];
	char pc0_str[10];
	char pc1_str[10];
	while(1)
	{
		itoa(num, num_str, 10);
		LCD_DrawString(20, 20, BLACK, WHITE, num_str, 16, 0);
		num++;

		itoa(poll_pc0(), pc0_str, 10);
		LCD_DrawString(20, 40, BLACK, WHITE, pc0_str, 16, 0);

		itoa(poll_pc1(), pc1_str, 10);
		LCD_DrawString(20, 60, BLACK, WHITE, pc1_str, 16, 0);

		nano_wait(ONE_MILLION * 10);
	}
	LCD_DrawRectangle(20, 20, 70, 90, GREEN);
}

void test_solenoid(void) {
	// solenoid: pb13, pc6-9
	init_pb13();
	init_pc6();
//	init_pc7();
//	init_pc8();
//	init_pc9();

	init_tft_lcd();
	init_pc0();
	char pc0_str[10];
	while(1) {
		if(poll_pc0()) {
			// not pressed
			set_pb13(0);
			set_pc6(0);
		} else {
			// pressed
			set_pb13(1);
			set_pc6(1);
		}
		itoa(poll_pc0(), pc0_str, 10);
		LCD_DrawString(20, 40, BLACK, WHITE, pc0_str, 16, 0);
	}



}

void test_servo(void) {
	uint16_t vals[3] = { 500, 1500, 2500 };
	int i = 0;

	init_pa8();
	init_tim1();

	while(1) {
		TIM1->CCR1 = vals[i++ % 3];
		nano_wait(ONE_BILLION);
	}
}


void test_leds(void) {
	init_ws2812b_leds();

	uint8_t r = 0;
	uint8_t g = 128;
	uint8_t b = 255;
	while(1) {
		nano_wait(ONE_THOUSAND * 5);
//		ws_insert_queue(0, r, g, b);
//		clear_ws_led_io_buffer(ws_io_buffer, 0);
		set_ws_led_io_buffer(ws_io_buffer, 0, r, g, b);


		// manually changing buffer before I add the clear signal after every color change
//		uint8_t rgb[] = {r,g,b};
//		for(int i = 0; i < 8; i++) {
//			for(int j = 0; j < 3; j++) {
//				uint16_t* t = ws_io_buffer;
//				t[(i * 3) + j] = rgb[j];
//			}
//		}

		display_buff();
		r = (r+25);
		g = (g+25);
		b = (b+125);
//		nano_wait(ONE_MILLION * 500);
//		ws_reset_led(0);
	}
}

//void enable_pc6() {
//	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
//
//	GPIOC->MODER |= 1 << (6 * 2); // set pc6 mode to output
//}
//void enable_tim3() {
//	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
//
//	TIM3->PSC = 4800-1;
//	TIM3->ARR = 15000-1;
//
//	TIM3->DIER |= TIM_DIER_UIE;
//	TIM3->DIER |= TIM_DIER_UDE;
//
//	TIM3->CR1 |= TIM_CR1_CEN;
//	NVIC_SetPriority(TIM3_IRQn, 0);
//	NVIC_EnableIRQ(TIM3_IRQn);
//}

//void enable_dma1() {
//	RCC->AHBENR |= RCC_AHBENR_DMAEN;
//
//	DMA1_Channel3->CCR |= DMA_CCR_MSIZE_1; // mem size = 32 bits
//	DMA1_Channel3->CCR |= DMA_CCR_PSIZE_1; //periph size = 32 bits
//	DMA1_Channel3->CCR |= DMA_CCR_MINC; // enable mem increment mode
//	DMA1_Channel3->CCR |= DMA_CCR_CIRC; // enable circular mode
//	DMA1_Channel3->CCR |= DMA_CCR_DIR; // set direction to mem2periph
//	DMA1_Channel3->CCR |= DMA_CCR_TCIE; // enable transfer complete interrupt
//	DMA1_Channel3->CNDTR = 1;
//	DMA1_Channel3->CPAR = (uint32_t)&GPIOC->BSRR;
//	DMA1_Channel3->CMAR = (uint32_t)&num;
//	NVIC_EnableIRQ(DMA1_Ch2_3_DMA2_Ch1_2_IRQn);
//
//}




void test_i2c(void) {

}

void test_audio(void) {

}
