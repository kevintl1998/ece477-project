#ifndef GAME_H
#define GAME_H

#include <stdint.h>

#define LIFE_COUNT_1 1
#define LIFE_COUNT_2 3
#define LIFE_COUNT_3 5
#define LIFE_COUNT_4 10

#define SCROLL_PAUSE_TIME (ONE_MILLION * 200)

typedef struct GameState {
	// variables for updating scoreboard rendering
	uint8_t left_button_pressed;
	uint8_t right_button_pressed;
	uint8_t select_button_pressed;

	// switch states

	// solenoid states
	// decremented by 1 in tim15 interrupt when they are continuously powered
	uint32_t left_paddle_active;
	uint32_t right_paddle_active;
	uint32_t obstacle1_active;
	uint32_t obstacle2_active;
	uint32_t obstacle3_active;

	// peripheral enabled
	uint8_t buttons_enabled;
	uint8_t switches_enabled;
	uint8_t solenoids_enabled;
	uint8_t servo_enabled;
	uint8_t leds_enabled;
	uint8_t audio_enabled;

	// starting life count option # (for choosing # of lives in main menu)
	uint8_t lives_option;

	uint8_t is_multiplayer;

	uint8_t lives_left;
	uint32_t score;
} GameState;

// global gamestate variable
extern GameState* gameState;

// list of all life options
extern uint8_t lives[];


void init_hardware(void);

void init_game(void);

int run_game(void);

#endif
