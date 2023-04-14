#include "releases/unit_test.h"

#include <stdlib.h>
#include <stdint.h>
#include "stm32f0xx.h"
#include <stm32f091xc.h>

#include "hardware/TFT_LCD_lib.h"
#include "hardware/STM32.h"
#include "hardware/ws2812b/WS2812B_LED.h"
#include "hardware/ws2812b/WS2812B_led_queue.h"
#include "hardware/audio/midi.h"
#include "hardware/audio/midiplay.h"

#include "interfacing/scoreboard.h"

#include "util.h"
#include "settings.h"



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
	test_i2c();
    if (DEVICE_ID == PLAYER1) {
        // test functions for p1
//    	test_scoreboard();
		test_servo();
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
    }
    return 0;
}


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
	// positions are when looking at the servo top down with the wire coming out of the top
	uint16_t continuous_clockwise = 500;
	uint16_t up_left = 1000;
	uint16_t left = 1500;
	uint16_t down_left = 2000;
	uint16_t down = 2500;

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

		nano_wait(ONE_THOUSAND);
		if(poll_pc0()) {
			TIM1->CCR1 = 0;
		} else if(poll_pc1()) {
			TIM1->CCR1 = 2250;
		} else if(poll_pc4()) {
			TIM1->CCR1 = 1750;
		}
		int v = TIM1->CCR1;
		itoa(v, v_str, 10);
		LCD_DrawString(20, 40, BLACK, WHITE, v_str, 16, 0);
	}
}


void test_leds(void) {
	init_ws2812b_leds();

	uint8_t r = 56;
	uint8_t g = 216;
	uint8_t b = 99;

	while(1) {
		nano_wait(ONE_BILLION);

		add_to_ws_queue(0, r, g, b, 500);
		add_to_ws_queue(0, r + 54, g + 85, b + 99, 500);
		add_to_ws_queue(1, r + 20, g, b + 211, 5000);
		add_to_ws_queue(1, r + 89, g + 4, b, 10000);
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

// The number of simultaneous voices to support.
#define VOICES 15

// An array of "voices".  Each voice can be used to play a different note.
// Each voice can be associated with a channel (explained later).
// Each voice has a step size and an offset into the wave table.
struct {
    uint8_t in_use;
    uint8_t note;
    uint8_t chan;
    uint8_t volume;
    int     step;
    int     offset;
} voice[VOICES];

MIDI_Player *mp;

// We'll use the Timer 6 IRQ to recompute samples and feed those
// samples into the DAC.
void TIM6_DAC_IRQHandler(void)
{
    // TODO: Remember to acknowledge the interrupt right here.
    TIM6->SR &= ~TIM_SR_UIF;

    int sample = 0;
    for(int x=0; x < sizeof voice / sizeof voice[0]; x++) {
        if (voice[x].in_use) {
            voice[x].offset += voice[x].step;
            if (voice[x].offset >= N<<16)
                voice[x].offset -= N<<16;
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

// Initialize the DAC so that it can output analog samples
// on PA4.  Configure it to be triggered by TIM6 TRGO.
void init_dac(void)
{
    // TODO: you fill this in. Ok
    RCC->APB1ENR |= RCC_APB1ENR_DACEN;
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    GPIOA->MODER |= 0x300;
    DAC->CR &= ~(DAC_CR_TSEL1_0 | DAC_CR_TSEL1_1 | DAC_CR_TSEL1_2);
    DAC->CR |= DAC_CR_TEN1;
    DAC->CR |= DAC_CR_EN1;
}

// Initialize Timer 6 so that it calls TIM6_DAC_IRQHandler
// at exactly RATE times per second.  You'll need to select
// a PSC value and then do some math on the system clock rate
// to determine the value to set for ARR.  Set it to trigger
// the DAC by enabling the Update Tigger in the CR2 MMS field.
void init_tim6(void)
{
    // TODO: you fill this in.
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
    TIM6->PSC = 0;
    TIM6->ARR = 48000000/RATE-1;
    TIM6->CR2 |= TIM_CR2_MMS_1;
    TIM6->DIER |= TIM_DIER_UIE;
    TIM6->CR1 |= TIM_CR1_CEN;
    NVIC->ISER[0] |= 1 << TIM6_DAC_IRQn;
}

// Find the voice current playing a note, and turn it off.
void note_off(int time, int chan, int key, int velo)
{
    int n;
    for(n=0; n<sizeof voice / sizeof voice[0]; n++) {
        if (voice[n].in_use && voice[n].note == key) {
            voice[n].in_use = 0; // disable it first...
            voice[n].chan = 0;   // ...then clear its values
            voice[n].note = key;
            voice[n].step = step[key];
            return;
        }
    }
}

// Find an unused voice, and use it to play a note.
void note_on(int time, int chan, int key, int velo)
{
    if (velo == 0) {
        note_off(time, chan, key, velo);
        return;
    }
    int n;
    for(n=0; n<sizeof voice / sizeof voice[0]; n++) {
        if (voice[n].in_use == 0) {
            voice[n].note = key;
            voice[n].step = step[key];
            voice[n].offset = 0;
            voice[n].volume = velo;
            voice[n].chan = chan;
            voice[n].in_use = 1;
            return;
        }
    }
}

void set_tempo(int time, int value, const MIDI_Header *hdr)
{
    // This assumes that the TIM2 prescaler divides by 48.
    // It sets the timer to produce an interrupt every N
    // microseconds, where N is the new tempo (value) divided by
    // the number of divisions per beat specified in the MIDI file header.
    TIM2->ARR = value/hdr->divisions - 1;
}

const float pitch_array[] = {
0.943874, 0.945580, 0.947288, 0.948999, 0.950714, 0.952432, 0.954152, 0.955876,
0.957603, 0.959333, 0.961067, 0.962803, 0.964542, 0.966285, 0.968031, 0.969780,
0.971532, 0.973287, 0.975046, 0.976807, 0.978572, 0.980340, 0.982111, 0.983886,
0.985663, 0.987444, 0.989228, 0.991015, 0.992806, 0.994599, 0.996396, 0.998197,
1.000000, 1.001807, 1.003617, 1.005430, 1.007246, 1.009066, 1.010889, 1.012716,
1.014545, 1.016378, 1.018215, 1.020054, 1.021897, 1.023743, 1.025593, 1.027446,
1.029302, 1.031162, 1.033025, 1.034891, 1.036761, 1.038634, 1.040511, 1.042390,
1.044274, 1.046160, 1.048051, 1.049944, 1.051841, 1.053741, 1.055645, 1.057552,
};

void pitch_wheel_change(int time, int chan, int value)
{
    //float multiplier = pow(STEP1, (value - 8192.0) / 8192.0);
    float multiplier = pitch_array[value >> 8];
    for(int n=0; n<sizeof voice / sizeof voice[0]; n++) {
        if (voice[n].in_use && voice[n].chan == chan) {
            voice[n].step = step[voice[n].note] * multiplier;
        }
    }
}

// An array of structures that say when to turn notes on or off.
struct {
    int when;
    uint8_t note;
    uint8_t volume;
} events[] = {
        {480,84,0x73}, {556,84,0x00}, {960,84,0x74}, {1008,84,0x00},
        {1440,91,0x76}, {1520,91,0x00}, {1920,91,0x79}, {1996,91,0x00},
        {2400,93,0x76}, {2472,93,0x00}, {2640,94,0x67}, {2720,94,0x00},
        {2880,96,0x67}, {2960,96,0x00}, {3120,93,0x6d}, {3180,93,0x00},
        {3360,91,0x79}, {3440,91,0x00}, {4320,89,0x70}, {4408,89,0x00},
        {4800,89,0x73}, {4884,89,0x00}, {5280,88,0x73}, {5360,88,0x00},
        {5760,91,0x79}, {5836,91,0x00}, {6240,86,0x79}, {6308,86,0x00},
        {6720,86,0x76}, {6768,86,0x00}, {7200,84,0x76}, {7252,84,0x00},
        {8160,84,0x73}, {8236,84,0x00}, {8640,84,0x74}, {8688,84,0x00},
        {9120,91,0x76}, {9200,91,0x00}, {9600,91,0x79}, {9676,91,0x00},
        {10080,93,0x76}, {10152,93,0x00}, {10320,94,0x67}, {10400,94,0x00},
        {10560,96,0x67}, {10640,96,0x00}, {10800,93,0x6d}, {10860,93,0x00},
        {11040,91,0x79}, {11120,91,0x00}, {12000,86,0x76}, {12080,86,0x00},
        {12480,86,0x73}, {12552,86,0x00}, {13440,84,0x6d}, {13440,88,0x73},
        {13508,88,0x00}, {13512,84,0x00}, {13920,86,0x76}, {14004,86,0x00},
        {14400,86,0x76}, {14472,86,0x00}, {15152,81,0x3b}, {15184,83,0x44},
        {15188,81,0x00}, {15220,84,0x46}, {15228,83,0x00}, {15248,86,0x57},
        {15264,84,0x00}, {15284,88,0x5c}, {15292,86,0x00}, {15308,89,0x68},
        {15320,88,0x00}, {15336,91,0x6d}, {15344,89,0x00}, {15364,93,0x6d},
        {15368,91,0x00}, {15460,93,0x00},
};

#if 1
int time = 0;
int n = 0;
void TIM2_IRQHandler(void)
{
    TIM2->SR &= ~TIM_SR_UIF;
    midi_play();
}
#endif



// Configure timer 2 so that it invokes the Update interrupt
// every n microseconds.  To do so, set the prescaler to divide
// by 48.  Then the CNT will count microseconds up to the ARR value.
// Basically ARR = n-1
// Set the ARPE bit in the CR1 so that the timer waits until the next
// update before changing the effective ARR value.
// Call NVIC_SetPriority() to set a low priority for Timer 2 interrupt.
// See the lab 6 text to understand how to do so.
void init_tim2(int n) {
    // TODO: you fill this in.
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    TIM2->PSC = 48;
    TIM2->ARR = n;
    TIM2->CR2 |= TIM_CR2_MMS_1;
    TIM2->CR1 |= TIM_CR1_ARPE;
    TIM2->DIER |= TIM_DIER_UIE;
    TIM2->CR1 |= TIM_CR1_CEN;
    NVIC->ISER[0] |= 1 << TIM2_IRQn;
}


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
