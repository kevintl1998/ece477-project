#include <stdint.h>

#include "stm32f091xc.h"

#include "hardware/STM32.h"
#include "hardware/ws2812b/WS2812B_LED.h"

#include "interfacing/solenoids.h"
#include "interfacing/buttons.h"
#include "interfacing/switches.h"

#include "game.h"

// timer 14 interrupt handler
// used to poll buttons and update their state
void TIM14_IRQHandler(void) {
    TIM14->SR &= ~TIM_SR_UIF;
    // timer 15 interrupt handler
    // used to update the state of the solenoids and switches
    uint8_t left = 0;
    uint8_t right = 0;
    uint8_t select = 0;

    if(gameState->buttons_enabled) {
    	left = poll_LB();
    	right = poll_RB();
    	select = poll_Select();
    }
    gameState->left_button_pressed = left;
    gameState->right_button_pressed = right;
    gameState->select_button_pressed = select;
}


void TIM15_IRQHandler(void) {
	TIM15->SR &= ~TIM_SR_UIF;

	if(gameState->switches_enabled) {
		// update switch states in gamestate
	}

	if(gameState->solenoids_enabled) {
		// update flipper solenoids
		update_left_flipper(gameState, poll_LB());
		update_right_flipper(gameState, poll_RB());

		// update solenoids activated by switches
		update_obstacle1(gameState, !poll_switch1());
		update_obstacle2(gameState, !poll_switch2());
		update_obstacle3(gameState, !poll_switch3());
		// update score and ball count activated by switches
	}
}


void TIM16_IRQHandler(void) {
	TIM16->SR &= ~TIM_SR_UIF;

	static uint8_t led_r = 100;
	static uint8_t led_g = 210;
	static uint8_t led_b = 43;
	// set led queue here
	// have var(s) in GameState for the led sequence(s) that
	// should be displayed(set by the timer whos peripheral those leds are close to),
	// then have this function decode them to display a specific led pattern
	if(gameState->leds_enabled) {
		for(int i = 0; i < WS_LED_COUNT; i++) {
			led_r += (i * 13); led_g += (i * 45); led_b += (i * 32);
			add_to_ws_queue(i, led_r, led_g, led_b, 500);
		}
	}
}


void TIM17_IRQHandler(void) {
	TIM17->SR &= ~TIM_SR_UIF;


}


void TIM3_IRQHandler(void) {

	if (TIM3->SR & TIM_SR_UIF) { // update interrupt
		TIM3->SR &= ~TIM_SR_UIF;
		//	DMA1_Channel3->CCR |= DMA_CCR_EN; // dma enable
	} else if (TIM3->SR & TIM_SR_CC1IF) { // cc1 interrupt
		TIM3->SR &= ~TIM_SR_CC1IF;

	} else if (TIM3->SR & TIM_SR_CC2IF) { // cc2 interrupt
		TIM3->SR &= ~TIM_SR_CC2IF;

	} else if (TIM3->SR & TIM_SR_CC3IF) { // cc3 interrupt
		TIM3->SR &= ~TIM_SR_CC3IF;

	} else if (TIM3->SR & TIM_SR_CC4IF) { // cc4 interrupt
		TIM3->SR &= ~TIM_SR_CC4IF;
	}
}

void DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler(void) {
	if (DMA1->ISR | DMA_ISR_TCIF3) { // transfer complete on channel 3 (for tim3)
		DMA1->IFCR |= DMA_IFCR_CTCIF3;
		// used for updating WS2812 LEDs
		ws_update_buffer();
	}
}



