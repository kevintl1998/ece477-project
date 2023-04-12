#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <stdint.h>

#include "game.h"

//extern const struct arrow;

//void init_led_spi(void);
// call this to initialize the lcd screen
void init_tft_lcd(void);

void start_menu_render(void);
void start_menu_options_render(void);
void score_display_render(void);

void start_menu_update();
void start_menu_options_update();
void score_display_update(GameState* gs);


#endif
