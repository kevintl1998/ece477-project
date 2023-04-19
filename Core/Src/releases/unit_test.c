#include "releases/unit_test.h"

#include <stdlib.h>
#include <stdint.h>
#include "stm32f0xx.h"
#include <stm32f091xc.h>
//#include "stm32f0xx_hal_uart.h"
#include "stm32f0xx_ll_usart.h"

#include "hardware/TFT_LCD_lib.h"
#include "hardware/STM32.h"
#include "hardware/ws2812b/WS2812B_LED.h"
#include "hardware/ws2812b/WS2812B_led_queue.h"
#include "hardware/audio/midi.h"
#include "hardware/audio/midiplay.h"
#include "hardware/audio/audio.h"

#include "interfacing/scoreboard.h"

#include "util.h"
#include "settings.h"


void test_usart(void);
void test_scoreboard(void);
void test_buttons(void);
void test_solenoid(void);
void test_servo(void);
void test_leds(void);
void test_i2c(void);
void test_switches(void);
void test_audio(void);
void test_gpio_led(void);


/*
 * Consider this the entry point when RELEASE_TYPE in main.c is set to UNIT_TEST
 */
int unit_test(void) {
    /* Every time a function is complete (eg: scoreboard is hooked up to microcontroller,
     * scoreboard functionality is complete, paddle functionality is complete, etc)
     * create a new test here for that function
     */

// Run unit tests for all functions here
//	test_i2c();
    if (DEVICE_ID == PLAYER1) {
        // test functions for p1
    	test_scoreboard();
//		test_servo();
//    	test_leds();
//    	test_usart();
//		test_audio();
    } else if(DEVICE_ID == PLAYER2) {
        // test functions for p2
//    	test_scoreboard();
//    	test_buttons(); // if running on the pcb make sure pull down resistors are enabled.
//    	test_solenoid();
//    	test_servo();
//    	test_leds();
//    	test_i2c();
//    	test_switches();
//    	test_audio();
//    	test_gpio_led();
    	test_usart();
    }
    return 0;
}


uint8_t usart_buffer;
void test_usart(void) {
	init_tft_lcd();
	uint8_t timer = 0;
	char buf_str[8];

#if DEVICE_ID == PLAYER1
	LL_USART_TransmitData8(USART1, timer);
	timer++;
#endif
	while(1) {
		if(USART1->ISR & USART_ISR_RXNE) {
			uint8_t recvd = LL_USART_ReceiveData8(USART1);
			itoa(recvd, buf_str, 10);
			LCD_DrawFillRectangle(10,0,100,30,WHITE);
			LCD_DrawString(10, 10, BLACK, WHITE, buf_str, 16, 10);
			timer++;
			LL_USART_TransmitData8(USART1, timer);
//			nano_wait(ONE_MILLION * 500);
		}
	}
}

//#if DEVICE_ID == PLAYER2
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) // triggers once uart has finished receiving data
//{
////    HAL_UART_Transmit(&huart1, UART1_rxBuffer, 12, 100);
//	if(huart->Instance == huart1.Instance) {
//		__HAL_UART_CLEAR_OREFLAG(huart);
//		__HAL_UART_SEND_REQ(huart, UART_RXDATA_FLUSH_REQUEST);
//		HAL_UART_Receive_IT(&huart1, (uint8_t*)bu, 11); // start data receive again
//	}
//}
//#endif


void test_scoreboard(void) {
	init_tft_lcd();

	start_menu_render();

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
	init_pc7();
	init_pc8();
	init_pc9();

	init_tft_lcd();
	init_pc0();
	char pc0_str[10];
	while(1) {
		if(poll_pc0()) {
			// pressed
			set_pb13(1);
			set_pc6(1);
			set_pc7(1);
			set_pc8(1);
			set_pc9(1);

		} else {
			// not pressed
			set_pb13(0);
			set_pc6(0);
			set_pc7(0);
			set_pc8(0);
			set_pc9(0);

		}
		itoa(poll_pc0(), pc0_str, 10);
		LCD_DrawString(20, 40, BLACK, WHITE, pc0_str, 16, 0);
	}

}

void test_servo(void) {
	// SERVO 1
//	uint16_t load_ball = 1600;
//	uint16_t get_ball = 2450;
	// SERVO 2
	uint16_t load_ball = 1500;
	uint16_t get_ball = 2425;


	// init buttons
	init_pc0();
	init_pc1();
	init_pc4();

	// init screen
	init_tft_lcd();

	// init servo
	init_pa8();
	init_tim1();
	char v_str[10];

	while(1) {
//		TIM1->CCR1 = vals[i++ % 3];

		nano_wait(ONE_MILLION);
		if(poll_pc0()) {
			TIM1->CCR1 = get_ball;
		} else if(poll_pc1()) {
			TIM1->CCR1 = load_ball;
		} else if(poll_pc4()) {
			TIM1->CCR1 = 1100;
		}
		uint16_t ccr = TIM1->CCR1;
		itoa(ccr, v_str, 10);
		LCD_DrawString(20, 40, BLACK, WHITE, v_str, 16, 0);
	}
}


void test_leds(void) {
#ifdef DEBUG_MODE
	init_tft_lcd();
#endif
	init_ws2812b_leds();

	uint8_t r = 56;
	uint8_t g = 216;
	uint8_t b = 99;

	while(1) {
		nano_wait(ONE_MILLION * 500);

		for(int i = 0; i < WS_LED_COUNT; i++) {
			set_led_color(i, r + (i*54), g + (i*23), b + (i*99));
//			add_to_ws_queue(i, r, g, b, 500);
//			add_to_ws_queue(i, r + 54, g + 85, b + 99, 50);
		}

//		add_to_ws_queue(0, r, g, b, 500);
//		add_to_ws_queue(0, r + 54, g + 85, b + 99, 500);
//		add_to_ws_queue(1, r + 20, g, b + 211, 5000);
//		add_to_ws_queue(1, r + 89, g + 4, b, 10000);
//		add_to_ws_queue(2, r + 20, g, b + 211, 5000);
//		add_to_ws_queue(2, r + 89, g + 4, b, 10000);
#ifdef DEBUG_MODE
		display_buff();
#endif
		r += 25; g += 30; b += 35;
//		r1 -= 20; r2 -= 15; r3 -= 10;
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

#if DEVICE_ID == PLAYER1
	nano_wait(ONE_THOUSAND);

#endif
#if DEVICE_ID == PLAYER2


#endif

}

void test_switches(void) {
	// test switches by togling the test led when any of the switches are pulled low

	// init switches
	init_pa0();
	init_pa1();
	init_pa2();
	init_pa3();
	init_pb0();
	init_pb1();
	init_pc5();

	// init gpio test led
	init_pb12();

	while(1) {
		set_pb12(!poll_pa0() || !poll_pa1() || !poll_pa2() || !poll_pa3() || !poll_pb0() || !poll_pb1() || !poll_pc5());
//		if(!poll_pa0() || !poll_pa1() || !poll_pa2() || !poll_pa3() || !poll_pb0() || !poll_pb1() || !poll_pc5()) {
//			set_pb12(1);
//		} else {
//			set_pb12(0);
//		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// init audio
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void test_audio(void) {
    init_wavetable_hybrid2();
    init_dac();
    init_tim6();
    mp = midi_init(midifile);
    // The default rate for a MIDI file is 2 beats per second
    // with 48 ticks per beat.  That's 500000/48 microseconds.
    init_tim2(10417);
}

void test_gpio_led(void) {
	//pb12
	init_pb12();
	uint8_t val = 1;
	while(1) {
		nano_wait(ONE_MILLION * 100);
		set_pb12(val);
		val = (val+1) % 2;
	}
}
