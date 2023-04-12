#include "game.h"

#include <stdlib.h>
#include "stm32f091xc.h"
#include "util.h"
#include "settings.h"

#include "hardware/stm32.h"
#include "hardware/TFT_LCD_lib.h"

#include "interfacing/scoreboard.h"
#include "interfacing/buttons.h"
#include "interfacing/leds.h"
#include "interfacing/switches.h"
#include "interfacing/solenoids.h"


// game structs
GameState __gameState;
GameState* gameState = &__gameState;

// rename timer reference for easier code reading
struct TIM_TypeDef *button_poll_timer = TIM14;


void init_hardware(void) {
	// INITIALIZE HARDWARE HERE


	// tft lcd
	init_tft_lcd();

	// leds
	init_leds();

	// audio


	// buttons
	init_LB();
	init_RB();
	init_Select();
	init_button_update_timer();

	// init switches
	init_switches();
	init_switch_poll_timer();

	// solenoid
	init_left_paddle();
	init_right_paddle();
	init_obstacles();

	// servo
}

void init_game(void) {
	// INIT GAME ELEMENTS (scoreboard, structs, etc) HERE

	// init structs


	// enable necessary peripherals for menu selection in gameState
	gameState->buttons_enabled = 1;
	gameState->leds_enabled = 1;
	gameState->audio_enabled = 1;
}

int run_game(void) {
	// choose single player or multiplayer
	start_menu_render();
	while(1) {
		uint8_t left = gameState->left_button_pressed;
		uint8_t right = gameState->right_button_pressed;
		uint8_t select = gameState->select_button_pressed;
		if(left || right) {
			gameState->is_multiplayer = gameState->is_multiplayer == 0 ? 1 : 0;
			score_display_update(gameState);
			nano_wait(ONE_MILLION * 200);
		} else if (select) {
#ifdef DEBUG_MODE
			if(gameState->is_multiplayer) {
				LCD_DrawString(180, 150, BLACK, WHITE, "Multi", 16, 0);
			} else {
				LCD_DrawString(180 ,150, BLACK, WHITE, "Single", 16, 0);
			}
#endif
			break;
		}
	}
//	// choose ball count
	start_menu_options_render();


	// start game
	// enable the rest of the peripherals required to play the game
	gameState->servo_enabled = 1;
	gameState->switches_enabled = 1;
	gameState->solenoids_enabled = 1;
	while(1) {
		// rendering will be done in this while loop
		// update score on scoreboard
		// update balls left on scoreboard
#ifdef DEBUG_MODE
		char s[10];
		itoa(gameState->left_button_pressed, s, 10);
		LCD_DrawString(10, 80, BLACK, WHITE, s, 16, 0);
		itoa(gameState->right_button_pressed, s, 10);
		LCD_DrawString(10, 95, BLACK, WHITE, s, 16, 0);
		itoa(gameState->select_button_pressed, s, 10);
		LCD_DrawString(10, 110, BLACK, WHITE, s, 16, 0);
#endif
		if(gameState->balls_left == 0) {
			// end game
			// disable peripherals
			// send end signal in multiplayer mode
			// wait for button press by player
			// break
		}
	}
	// reset game
    return 0;
}
