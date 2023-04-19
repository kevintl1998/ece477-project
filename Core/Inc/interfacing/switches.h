#ifndef SWITCHES_H
#define SWITCHES_H

void init_switches(void);
void init_switch_poll_timer(void);

int poll_switch1(void); // controls obstacle 1
int poll_switch2(void); // controls obstacle 2
int poll_switch3(void); // controls obstacle 3
int poll_switch4(void); // detects if ball goes out of bounds
int poll_switch5(void);
int poll_switch6(void);
int poll_switch7(void);

#endif
