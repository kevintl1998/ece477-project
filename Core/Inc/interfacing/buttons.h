#ifndef BUTTONS_H
#define BUTTONS_H

void init_LB();
void init_RB();
void init_Select();

int poll_LB();
int poll_RB();
int poll_Select();

void init_button_update_timer();

#endif
