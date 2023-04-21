#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include "settings.h"

#define NEGATIVE_ONE (uint32_t)(-1)

#define SERVO_MAX_ACTIVE_TIME 1000

#if SERVO_TYPE == WORKING_SERVO
// player 1 (red light)
#define SERVO_LOAD_BALL 1625
#define SERVO_GET_BALL 2450
#endif
#if SERVO_TYPE == BROKE_SERVO
// player 2 (green light)
#define SERVO_LOAD_BALL 1500
#define SERVO_GET_BALL 2300
#endif


#define GAMEMODE_NULL (uint8_t)(0-1)
#define GAMEMODE_SINGLEPLAYER 0
#define GAMEMODE_MULTIPLAYER 1

#define LIFE_COUNT_1 1
#define LIFE_COUNT_2 3
#define LIFE_COUNT_3 5
#define LIFE_COUNT_4 10

#define SCROLL_PAUSE_TIME (ONE_MILLION * 175)
#define MENU_WAIT_TIME (ONE_MILLION * 175)

typedef struct GameState {
	// variables for updating scoreboard rendering
	volatile uint8_t left_button_pressed;
	volatile uint8_t right_button_pressed;
	volatile uint8_t select_button_pressed;

	// switch states

	// solenoid states
	// decremented by 1 in tim15 interrupt when they are continuously powered
	volatile uint32_t left_paddle_active;
	volatile uint32_t right_paddle_active;
	uint32_t obstacle1_active;
	uint32_t obstacle2_active;
	uint32_t obstacle3_active;
	uint32_t pop_bumper_active;
	uint32_t servo_active;

	// peripheral enabled
	uint8_t buttons_enabled;
	uint8_t switches_enabled;
	uint8_t solenoids_enabled;
	uint8_t servo_enabled;
	uint8_t leds_enabled;
	uint8_t audio_enabled;

	// for syncing game start and game end between the mcus
	uint8_t player_ready;
	uint8_t other_ready;

	// starting life count option # (for choosing # of lives in main menu)
	uint8_t lives_option;

	volatile uint8_t gameMode; // singleplayer or multiplayer

	volatile uint8_t lives_left;
	volatile uint32_t score;

	// score and life cound of other player
	volatile uint32_t other_score;
	volatile uint32_t other_lives;
} GameState;

// global gamestate variable
extern volatile GameState* gameState;

// list of all life options
extern uint8_t lives[];


void init_hardware(void);

void init_game(void);

int run_game(void);

#endif
