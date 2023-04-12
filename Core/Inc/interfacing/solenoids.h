#ifndef SOLENOIDS_H
#define SOLENOIDS_H

#include "game.h"

// time in 1/100th of a second
#define FLIPPER_MAX_ACTIVE_TIME 100

#define POP_BUMPER_MAX_ACTIVE_TIME 100

void init_left_paddle(void);
void init_right_paddle(void);
void init_obstacles(void);

void update_left_flipper(GameState* gs, uint8_t LB_state);
void update_right_flipper(GameState* gs, uint8_t RB_state);

void update_obstacle1(GameState* gs, uint8_t switch1_state);
void update_obstacle2(GameState* gs, uint8_t switch2_state);
void update_obstacle3(GameState* gs, uint8_t switch3_state);

#endif
