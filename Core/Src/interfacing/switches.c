#include "interfacing/switches.h"

#include "hardware/STM32.h"

void init_switches(void) {
	 init_pa0();
	 init_pa1();
	 init_pa2();
	 init_pa3();
	 init_pb0();
	 init_pb1();
	 init_pc5();
}

void init_switch_poll_timer(void) {
	init_tim15();
}

int poll_switch1() {
	return poll_pa0();
}

int poll_switch2() {
	return poll_pa1();
}

int poll_switch3() {
	return poll_pa2();
}

int poll_switch4() {
	return poll_pa3();
}

int poll_switch5() {
	return poll_pb0();
}

int poll_switch6() {
	return poll_pb1();
}

int poll_switch7() {
	return poll_pc5();
}
