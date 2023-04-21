#ifndef SOLENOIDS_H
#define SOLENOIDS_H

#include "game.h"

#define FLIPPER_MAX_ACTIVE_TIME 100

#define POP_BUMPER_MAX_ACTIVE_TIME 10

void init_left_paddle(void);
void init_right_paddle(void);
void init_obstacles(void);

void update_left_flipper(volatile GameState* gs, uint8_t LB_state);
void update_right_flipper(volatile GameState* gs, uint8_t RB_state);

void update_obstacle1(volatile GameState* gs, uint8_t switch1_state);
void update_obstacle2(volatile GameState* gs, uint8_t switch2_state);
void update_obstacle3(volatile GameState* gs, uint8_t switch3_state);
void update_pop_bumper(volatile GameState* gs, uint8_t pop_bumper_state);
void update_servo(volatile GameState* gs, uint8_t servo_state);

#endif
