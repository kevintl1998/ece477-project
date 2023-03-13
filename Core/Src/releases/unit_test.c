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
    	test_scoreboard();
    }

    return 0;
}

void test_scoreboard(void) {
	init_tft_lcd();

	LCD_DrawRectangle(20, 20, 70, 90, GREEN);


}
