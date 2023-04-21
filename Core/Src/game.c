#include "game.h"

#include <stdlib.h>
#include "stm32f091xc.h"
#include "util.h"
#include "settings.h"

#include "hardware/stm32.h"
#include "hardware/TFT_LCD_lib.h"
#include "hardware/ws2812b/WS2812B_LED.h"

#include "interfacing/scoreboard.h"
#include "interfacing/buttons.h"
#include "interfacing/leds.h"
#include "interfacing/switches.h"
#include "interfacing/solenoids.h"
#include "interfacing/mcu_comms.h"


// game structs
volatile GameState __gameState;
volatile GameState* gameState = &__gameState;

// list of all life options
uint8_t lives[] = {LIFE_COUNT_1, LIFE_COUNT_2, LIFE_COUNT_3, LIFE_COUNT_4};

// rename timer reference for easier code reading
//struct TIM_TypeDef *button_poll_timer = TIM14;

void choose_gamemode(void);
void choose_life_count(void);
void get_options_from_other(void);
void wait_for_ready(uint8_t can_press_select, uint8_t can_press_left, uint8_t can_press_right);
void debug_print_options(void);

void init_hardware(void) {
	// INITIALIZE HARDWARE HERE


	// tft lcd
	init_tft_lcd();

	// leds
	init_leds();
	init_led_timer();
	for(int i = 0; i < WS_LED_COUNT; i++) {
		set_led_color(i, 0, 0, 255);
	}

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
	init_pa8();
	init_tim1();

	// mcu communication
	init_comms();
}

void init_game(void) {
	// INIT GAME ELEMENTS (scoreboard, structs, etc) HERE

	// init struct(s)

	// set starting life count option
	gameState->lives_option = 0;
	gameState->gameMode = GAMEMODE_NULL;


	// enable necessary peripherals for menu selection in gameState
	gameState->servo_enabled = 0;
	gameState->switches_enabled = 0;
	gameState->solenoids_enabled = 0;

	gameState->buttons_enabled = 1;
	gameState->leds_enabled = 0;
//	gameState->audio_enabled = 1;
}

int run_game(void) {



#if DEVICE_ID == PLAYER1
	start_menu_render();
	choose_gamemode();
	start_menu_options_render();
	choose_life_count();
	send_game_options(gameState);
#endif


#if DEVICE_ID == PLAYER2
	// player 2 wait for player 1 to choose options
	get_options_from_other();
	if(gameState->gameMode == GAMEMODE_SINGLEPLAYER) {
		start_menu_options_render();
		choose_life_count();
	}
#endif


	debug_print_options();

	wait_for_ready(1,0,0);

	// enable the rest of the peripherals required to play the game
	gameState->servo_enabled = 1;
	gameState->switches_enabled = 1;
	gameState->solenoids_enabled = 1;
	gameState->leds_enabled = 1;

	 // change to device id == if multiplayer can work
	if(SERVO_TYPE == BROKE_SERVO) {
		init_audio();
	}

	// game start
	score_display_render(gameState);

#ifdef DEBUG_MODE
//	gameState->lives_left = 10;
#endif

	// main game loop
	uint32_t prev_score = 0;
	uint32_t prev_lives = 0;
	while(1) {
		// rendering will be done in this while loop
		// update score on scoreboard
		// update balls left on scoreboard
		if(prev_score != gameState->score || prev_lives != gameState->lives_left) {
			score_display_update(gameState);
			prev_score = gameState->score;
			prev_lives = gameState->lives_left;
		}
		if(gameState->lives_left == 0
				|| (gameState->gameMode == GAMEMODE_MULTIPLAYER && gameState->other_lives == 0)) {
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
#if DEVICE_ID != PLAYER1
		gameState->lives_left -= 1;
#endif

#endif

	nano_wait(ONE_MILLION * 100);
	}


	// end game
	// disable peripherals
	gameState->servo_enabled = 0;
	gameState->switches_enabled = 0;
	gameState->solenoids_enabled = 0;
	gameState->leds_enabled = 0;


	if(gameState->gameMode == GAMEMODE_MULTIPLAYER) {
		// sync the scores
		send_lives(gameState);
		nano_wait(MENU_WAIT_TIME);
		send_score(gameState);
	}

	gameover_render(gameState);

	nano_wait(MENU_WAIT_TIME);
	wait_for_ready(1,1,1);


	// reset game
	hard_reset();
    return 0;
}

void choose_gamemode(void) {
	while(1) {
		uint8_t left = gameState->left_button_pressed;
		uint8_t right = gameState->right_button_pressed;
		uint8_t select = gameState->select_button_pressed;
		if(left || right) {
			gameState->gameMode = gameState->gameMode == GAMEMODE_SINGLEPLAYER ? GAMEMODE_MULTIPLAYER : GAMEMODE_SINGLEPLAYER;
			start_menu_update(gameState);
			nano_wait(MENU_WAIT_TIME);
		} else if (select) {
			nano_wait(MENU_WAIT_TIME);
			break;
		}
	}
}

void choose_life_count(void) {
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
			nano_wait(MENU_WAIT_TIME);
		} else if(right) {
			gameState->lives_option = (gameState->lives_option + 1) % 4;
			start_menu_options_update(gameState);
			nano_wait(MENU_WAIT_TIME);
		} else if (select) {
			gameState->lives_left = lives[gameState->lives_option];
			if(gameState->gameMode == GAMEMODE_MULTIPLAYER) {
				gameState->other_lives = lives[gameState->lives_option];
			}
			nano_wait(MENU_WAIT_TIME);
			break;
		}
	}
}

void get_options_from_other(void) {
	while(1) {
		if(gameState->gameMode != GAMEMODE_NULL) {
			nano_wait(MENU_WAIT_TIME);
			break;
		}
	}
}

void wait_for_ready(uint8_t can_press_select, uint8_t can_press_left, uint8_t can_press_right) {
	if(!(can_press_select || can_press_left || can_press_right)) return;
	// both players ready up
	// wait for other player to ready up
	while(1) {
		uint8_t left = can_press_left ? gameState->left_button_pressed : 0;
		uint8_t right = can_press_right ? gameState->right_button_pressed : 0;
		uint8_t select = can_press_select ? gameState->select_button_pressed : 0;

		if(select || left || right) {
			// when player presses select, send player ready signal to other player

			if(gameState->gameMode == GAMEMODE_MULTIPLAYER) {
				send_player_ready();
				while(!gameState->other_ready); // wait for other player to ready
			}
			nano_wait(MENU_WAIT_TIME);
			break;
		}
	}
}

void debug_print_options(void) {
#ifdef DEBUG_MODE
	// displays the chosen options
	if(gameState->gameMode == GAMEMODE_MULTIPLAYER) {
		LCD_DrawString(0, 150, BLACK, WHITE, "Multi", 16, 0);
	} else {
		LCD_DrawString(0 ,150, BLACK, WHITE, "Single", 16, 0);
	}
	char life_str[2];
	itoa(gameState->lives_left, life_str, 10);
	LCD_DrawString(0, 170, BLACK, WHITE, life_str, 16, 0);
#endif
}
