#include "game.h"

#include "interfacing/scoreboard.h"
#include "interfacing/buttons.h"
#include "interfacing/leds.h"

void init_hardware(void) {
	// INITIALIZE HARDWARE HERE

	// tft lcd
	init_tft_lcd();

	// leds
	init_leds();

	// audio


	// buttons
	init_left_button();
	init_right_button();
	init_select_button();
	init_button_poll_timer();

	// init switches
	init_switches();
	init_switch_poll_timer();

	// solenoid

	// servo
}

void init_game(void) {
	// INIT GAME ELEMENTS (scoreboard, structs, etc) HERE
}

int start_game(void) {
    return 0;
}
