#include <stdint.h>
#include "stm32f091xc.h"
#include "hardware/STM32.h"
#include "hardware/ws2812b/WS2812B_LED.h"

// timer 14 interrupt handler code
/*
void TIM14_IRQHandler(void) {
    TIM14->SR &= ~TIM_SR_UIF;
    uint32_t v = poll_pc12(); // poll value of pc12(button) in input data register
    if (v == 1) {
        update_pc9(0);
    } else {
        update_pc9(1);
    }
}
*/


uint32_t tim3_dma_ctr = 0;

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



