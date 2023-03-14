#include "releases/unit_test.h"
#include "hardware/TFT_LCD.h"
#include "hardware/TFT_LCD_legacy.h"
#include "util.h"
#include <stdlib.h>
#include "hardware/STM32.h"
#include "settings.h"
#include <stdint.h>
#include "stm32f0xx.h"

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

}

void test_i2c(void) {

}

void test_audio(void) {

}
