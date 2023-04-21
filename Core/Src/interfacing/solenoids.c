#include "interfacing/solenoids.h"

#include "hardware/STM32.h"



void init_left_paddle(void)  { init_pb13(); } // solenoid 5
void init_right_paddle(void) { init_pc6(); } // solenoid 4

void init_obstacle1(void) 	 { init_pc7(); }
void init_obstacle2(void) 	 { init_pc8(); }
void init_obstacle3(void) 	 { init_pc9(); }
void init_obstacles(void) {
	init_obstacle1();
	init_obstacle2();
	init_obstacle3();
}

void update_solenoid(void (*set_state)(uint8_t), uint8_t B_state, uint32_t* active_time, uint32_t max_active_time) {
	if(B_state) {
		if(*active_time > 1) {
			(*active_time)--;
			set_state(1);
		} else if(*active_time == 1) {
			(*active_time) = -1;
			set_state(0);
		} else if (*active_time == 0) {
			(*active_time) = max_active_time;
			set_state(1);
		}
	} else {
		// an attempt at hacky debouncing (did not work)
//		if((*active_time) == 0) {
//			(*active_time) = 10;
//		} else if((*active_time == -1)) {
//			(*active_time) = 0;
//			set_state(0);
//		}

		(*active_time) = 0;
		set_state(0);
	}
}

void update_left_flipper(volatile GameState* gs, uint8_t LB_state) {
	update_solenoid(set_pb13, LB_state, &gs->left_paddle_active, FLIPPER_MAX_ACTIVE_TIME);
}
void update_right_flipper(volatile GameState* gs, uint8_t RB_state) {
	update_solenoid(set_pc6, RB_state, &gs->right_paddle_active, FLIPPER_MAX_ACTIVE_TIME);
}

void update_obstacle1(volatile GameState* gs, uint8_t switch1_state) {
	update_solenoid(set_pc7, switch1_state, &gs->obstacle1_active, POP_BUMPER_MAX_ACTIVE_TIME);
}
void update_obstacle2(volatile GameState* gs, uint8_t switch2_state) {
	update_solenoid(set_pc8, switch2_state, &gs->obstacle2_active, POP_BUMPER_MAX_ACTIVE_TIME);
}
void update_obstacle3(volatile GameState* gs, uint8_t switch3_state) {
	update_solenoid(set_pc9, switch3_state, &gs->obstacle3_active, POP_BUMPER_MAX_ACTIVE_TIME);
}

void update_pop_bumper(volatile GameState* gs, uint8_t pop_bumper_state) {
	update_solenoid(set_pc7, pop_bumper_state, &gs->pop_bumper_active, POP_BUMPER_MAX_ACTIVE_TIME);
}

void set_servo(uint8_t value) {
	if(value) {
		TIM1->CCR1 = SERVO_LOAD_BALL;
	} else {
		TIM1->CCR1 = SERVO_GET_BALL;
	}
}

void update_servo(volatile GameState* gs, uint8_t servo_state) {
	update_solenoid(set_servo, servo_state, &gs->servo_active, SERVO_MAX_ACTIVE_TIME);
}
