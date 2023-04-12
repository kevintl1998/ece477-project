#ifndef GAME_H
#define GAME_H

#include <stdint.h>

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

	uint8_t is_multiplayer;

	uint8_t balls_left;
	uint32_t score;
} GameState;
extern GameState* gameState;

void init_hardware(void);

void init_game(void);

int run_game(void);

#endif
