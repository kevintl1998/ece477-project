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
#include "interfacing/mcu_comms.h"


// game structs
GameState __gameState;
GameState* gameState = &__gameState;

// list of all life options
uint8_t lives[] = {LIFE_COUNT_1, LIFE_COUNT_2, LIFE_COUNT_3, LIFE_COUNT_4};

// rename timer reference for easier code reading
//struct TIM_TypeDef *button_poll_timer = TIM14;


void init_hardware(void) {
	// INITIALIZE HARDWARE HERE


	// tft lcd
	init_tft_lcd();

	// leds
	init_leds();
	init_led_timer();

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

	// mcu communication
	init_comms();
}

void init_game(void) {
	// INIT GAME ELEMENTS (scoreboard, structs, etc) HERE

	// init struct(s)

	// set starting life count option
	gameState->lives_option = 0;


	// enable necessary peripherals for menu selection in gameState
	gameState->servo_enabled = 0;
	gameState->switches_enabled = 0;
	gameState->solenoids_enabled = 1;

	gameState->buttons_enabled = 1;
//	gameState->leds_enabled = 1;
	gameState->audio_enabled = 1;
}

int run_game(void) {


	// choose single player or multiplayer
#if DEVICE_ID == PLAYER1
	// player 1 chooses gamemode and game options
	start_menu_render();
	while(1) {
		uint8_t left = gameState->left_button_pressed;
		uint8_t right = gameState->right_button_pressed;
		uint8_t select = gameState->select_button_pressed;
		if(left || right) {
			gameState->is_multiplayer = gameState->is_multiplayer == 0 ? 1 : 0;
			start_menu_update(gameState);
			nano_wait(SCROLL_PAUSE_TIME);
		} else if (select) {
			nano_wait(SCROLL_PAUSE_TIME);
			break;
		}
	}

//	 choose ball count
	start_menu_options_render();
	while(1) {
		uint8_t left = gameState->left_button_pressed;
		uint8_t right = gameState->right_button_pressed;
		uint8_t select = gameState->select_button_pressed;
		if(left) {
			if(gameState->lives_option == 0) {
				gameState->lives_option = 3;
			} else {
				gameState->lives_option = (gameState->lives_option - 1);
			}
			start_menu_options_update(gameState);
			nano_wait(SCROLL_PAUSE_TIME);
		} else if(right) {
			gameState->lives_option = (gameState->lives_option + 1) % 4;
			start_menu_options_update(gameState);
			nano_wait(SCROLL_PAUSE_TIME);
		} else if (select) {
			gameState->lives_left = lives[gameState->lives_option];
			nano_wait(SCROLL_PAUSE_TIME);
			break;
		}
	}
	// after player1 finishes choosing, send options to p2
	send_game_options(gameState);

#endif


#if DEVICE_ID == PLAYER2
	// player 2 wait for player 1 to choose options
	while(1) {
		if(gameState->lives_left != 0) {
			break;
		}
	}
#endif

#ifdef DEBUG_MODE
	// displays the chosen options
	if(gameState->is_multiplayer) {
		LCD_DrawString(0, 150, BLACK, WHITE, "Multi", 16, 0);
	} else {
		LCD_DrawString(0 ,150, BLACK, WHITE, "Single", 16, 0);
	}
	char life_str[2];
	itoa(gameState->lives_left, life_str, 10);
	LCD_DrawString(0, 170, BLACK, WHITE, life_str, 16, 0);
#endif

	// both players ready up
	if(gameState->is_multiplayer) {
		// wait for other player to ready up
		while(1) {
			uint8_t select = gameState->select_button_pressed;
			if(select) {
				// when player presses select, send player ready signal to other player
				send_player_ready();
				while(!gameState->other_ready); // wait for other player to ready
				break;
			}
		}
	}

	// enable the rest of the peripherals required to play the game
	gameState->servo_enabled = 1;
	gameState->switches_enabled = 1;
	gameState->solenoids_enabled = 1;

	// game start
	score_display_render(gameState);

#ifdef DEBUG_MODE
//	gameState->lives_left = 10;
#endif

	uint32_t prev_score = 0;
	uint32_t prev_lives = gameState->lives_left;
	while(1) {
		// rendering will be done in this while loop
		// update score on scoreboard
		// update balls left on scoreboard
		if(prev_score != gameState->score || prev_lives != gameState->lives_left) {
			score_display_update(gameState);
			prev_score = gameState->score;
			prev_lives = gameState->lives_left;
		}
		if(gameState->lives_left == 0) {
			// break
			break;
		}
#ifdef DEBUG_MODE
		char s[10];
		itoa(gameState->left_button_pressed, s, 10);
		LCD_DrawString(10, 80, BLACK, WHITE, s, 16, 0);
		itoa(gameState->right_button_pressed, s, 10);
		LCD_DrawString(10, 95, BLACK, WHITE, s, 16, 0);
		itoa(gameState->select_button_pressed, s, 10);
		LCD_DrawString(10, 110, BLACK, WHITE, s, 16, 0);
		gameState->score += 100;
//		gameState->lives_left -= 1;
#endif

	nano_wait(ONE_MILLION * 100);
	}


	// end game
	// disable peripherals
	gameState->servo_enabled = 0;
	gameState->switches_enabled = 0;
	gameState->solenoids_enabled = 0;


	if(gameState->is_multiplayer) {

		// send end signal in multiplayer mode

		// do 1 final score sync



	}

	gameover_render(gameState);

	// wait for button press by player
	while(1) {
		uint8_t left = gameState->left_button_pressed;
		uint8_t right = gameState->right_button_pressed;
		uint8_t select = gameState->select_button_pressed;
		if(left || right || select) {
			break;
		}
	}

	// wait for other player to press button
	if(gameState->is_multiplayer) {

	}


	// reset game
	hard_reset();
    return 0;
}
