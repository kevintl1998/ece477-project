#include "interfacing/buttons.h"

#include "hardware/stm32.h"



void init_LB() {
	init_pc0();
}
void init_RB() {
	init_pc1();
}
void init_Select() {
	init_pc4();
}

int poll_LB() {
	return poll_pc0();
}
int poll_RB() {
	return poll_pc1();
}

int poll_Select() {
	return poll_pc4();
}


void init_button_update_timer() {
	init_tim14();
}

