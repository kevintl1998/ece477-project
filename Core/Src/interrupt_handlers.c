#include <stdint.h>

#include "stm32f091xc.h"

#include "hardware/STM32.h"
#include "hardware/ws2812b/WS2812B_LED.h"
#include "hardware/audio/audio.h"
#include "hardware/TFT_LCD_lib.h"

#include "interfacing/solenoids.h"
#include "interfacing/buttons.h"
#include "interfacing/switches.h"
#include "interfacing/mcu_comms.h"

#include "settings.h"
#include "game.h"
#include "util.h"

uint8_t led_r = 23;
uint8_t led_g = 84;
uint8_t led_b = 96;
uint32_t life_cooldown = NEGATIVE_ONE;
uint32_t score_cooldown = NEGATIVE_ONE;
void EXTI2_3_IRQHandler(void) {
	if (EXTI->PR & EXTI_PR_PR3) { // triggered by pa3
	   EXTI->PR |= EXTI_PR_PR3;
	   // player loses life
	   if(gameState->lives_left != 0 && life_cooldown == NEGATIVE_ONE) {
		   gameState->lives_left -= 1;
		   life_cooldown = 25;
	   }
	}
	if(EXTI->PR & EXTI_PR_PR2) { // triggered by pa2
		EXTI->PR |= EXTI_PR_PR2;
		// pop bumper activated
		if(score_cooldown == NEGATIVE_ONE) {
			gameState->score += 100;
			gameState->pop_bumper_active = POP_BUMPER_MAX_ACTIVE_TIME;
			score_cooldown = 25;
			led_r += 40; led_g += 54; led_b += 23;
			for(int i = 0; i < WS_LED_COUNT; i++) {
				set_led_color(i, led_r, led_g, led_b);
			}
		}
	}
}

// timer 14 interrupt handler
// used to poll buttons and update their state
void TIM14_IRQHandler(void) {
    TIM14->SR &= ~TIM_SR_UIF;

    static uint8_t left_history;
    static uint8_t right_history;
    static uint8_t select_history;

	#define MAX_HOLD 6
	#define HOLD_ON 3

    update_debounce_history(&left_history, poll_LB(), MAX_HOLD);
    update_debounce_history(&right_history, poll_RB(), MAX_HOLD);
    update_debounce_history(&select_history, poll_Select(), MAX_HOLD);

    gameState->left_button_pressed = left_history > HOLD_ON ? 1 : 0;
    gameState->right_button_pressed = right_history > HOLD_ON ? 1 : 0;
    gameState->select_button_pressed = select_history > HOLD_ON ? 1 : 0;
}


void TIM15_IRQHandler(void) {
	TIM15->SR &= ~TIM_SR_UIF;
    // timer 15 interrupt handler
    // used to update the state of the solenoids and switches

	if(gameState->switches_enabled) {
		// update switch states in gamestate
	}

	if(gameState->solenoids_enabled) {
		// update flipper solenoids
		update_left_flipper(gameState, poll_LB());
		update_right_flipper(gameState, poll_RB());

		// update solenoids activated by switches
//		update_obstacle1(gameState, !poll_switch1());
//		update_obstacle2(gameState, !poll_switch2());
//		update_obstacle3(gameState, !poll_switch3());
		// update score and ball count activated by switches

		// if pop bumper active, activate solenoid for
		if(gameState->pop_bumper_active > 0 && gameState->pop_bumper_active < NEGATIVE_ONE) {
			update_pop_bumper(gameState, 1);
		}
		if(score_cooldown != NEGATIVE_ONE) {
			score_cooldown -= 1;
		}
		if(life_cooldown != NEGATIVE_ONE) {
			life_cooldown -= 1;
		}
	}
	if(gameState->servo_enabled) {
		update_servo(gameState, poll_Select());
	}
}

// interrupt for updating led values
uint32_t led_time = 0;
void TIM16_IRQHandler(void) {
	TIM16->SR &= ~TIM_SR_UIF;
//	static uint32_t led_time;
	static uint8_t led_r;
	static uint8_t led_g;
	static uint8_t led_b;
	// set led queue here
	// have var(s) in GameState for the led sequence(s) that
	// should be displayed(set by the timer whos peripheral those leds are close to),
	// then have this function decode them to display a specific led pattern

//	if(gameState->leds_enabled && led_time == 1) {
//		for(int i = 0; i < WS_LED_COUNT; i++) {
////			led_r += ((i + 1) * 13); led_g += ((i + 1) * 45); led_b += ((i + 1) * 32);
//			led_r += 25; led_g += 25; led_b += 25;
//			set_led_color(i, led_r, led_g, led_b);
//		}
//	}
	led_time = (led_time + 1) % 200;
}

// interrupt for polling usart
void TIM17_IRQHandler(void) {
	TIM17->SR &= ~TIM_SR_UIF;

	send_data();
	recv_data();
}

// ========== AUDIO ==========


void TIM6_DAC_IRQHandler(void)
{
    TIM6->SR &= ~TIM_SR_UIF;
    // We'll use the Timer 6 IRQ to recompute samples and feed those
    // samples into the DAC.
    int sample = 0;
    for(int x=0; x < VOICES; x++) {
        if (voice[x].in_use) {
            voice[x].offset += voice[x].step;
            if (voice[x].offset >= WAVETABLE_SIZE<<16)
                voice[x].offset -= WAVETABLE_SIZE<<16;
            sample += (wavetable[voice[x].offset>>16] * voice[x].volume) >> 4;
        }
    }
    sample = (sample >> 10) + 2048;
    if (sample > 4095)
        sample = 4095;
    else if (sample < 0)
        sample = 0;
    DAC->DHR12R1 = sample;
    if (mp->nexttick == MAXTICKS)
        mp = midi_init(midifile);
}

#if 1
int time = 0;
int n = 0;
void TIM2_IRQHandler(void)
{
    TIM2->SR &= ~TIM_SR_UIF;

    midi_play();
}
#endif

// ========================

void DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler(void) {
	if (DMA1->ISR | DMA_ISR_TCIF3) { // transfer complete on channel 3 (for tim3)
		DMA1->IFCR |= DMA_IFCR_CTCIF3;
		// used for updating WS2812 LEDs
//		ws_update_buffer();
	}
}

// not used
void TIM3_IRQHandler(void) {
	if (TIM3->SR & TIM_SR_UIF) { // update interrupt
		TIM3->SR &= ~TIM_SR_UIF;
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
