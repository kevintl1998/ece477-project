#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <stdint.h>

#include "hardware/TFT_LCD_lib.h"

#include "game.h"

// global scoreboard constants
#if USE_HORIZONTAL == 0 || USE_HORIZONTAL == 2
#define SCOREBOARD_W LCD_W
#define SCOREBOARD_H LCD_H
#endif
#if USE_HORIZONTAL == 1 || USE_HORIZONTAL == 3
#define SCOREBOARD_WIDTH LCD_H
#define SCOREBOARD_HEIGHT LCD_W
#endif


// gamemode select screen constants
#define GAMEMODE_SELECT_LOGO_X 		0
#define GAMEMODE_SELECT_LOGO_Y 		0
#define SINGLE_TEXT_X 				10
#define SINGLE_TEXT_Y 				125
#define MULTI_TEXT_X 				250
#define MULTI_TEXT_Y 				SINGLE_TEXT_Y
#define GAMEMODE_SELECTOR_SINGLE_X 	20
#define GAMEMODE_SELECTOR_MULTI_X	280
#define GAMEMODE_SELECTOR_Y 		(SINGLE_TEXT_Y + 25)
#define CORNER_SUN_X 				0
#define CORNER_SUN_Y 				(SCOREBOARD_HEIGHT - corner_sun.height)


// lives select screen constants
#define LIVES_OPTIONS_LOGO_X 			35
#define LIVES_OPTIONS_LOGO_Y 			10
#define NUM_LIVES_OPTION_TEXT_X 		50
#define NUM_LIVES_OPTION_TEXT_Y 		90
#define LIVES_OPTIONS_SPACING 			50
#define LIVES_OPTIONS_BASE_X 			70
#define LIVES_OPTION_1_X 				(LIVES_OPTIONS_BASE_X + LIVES_OPTIONS_SPACING * 0)
#define LIVES_OPTION_3_X 				(LIVES_OPTIONS_BASE_X + LIVES_OPTIONS_SPACING * 1)
#define LIVES_OPTION_5_X 				(LIVES_OPTIONS_BASE_X + LIVES_OPTIONS_SPACING * 2)
#define LIVES_OPTION_10_X 				(LIVES_OPTIONS_BASE_X + LIVES_OPTIONS_SPACING * 3)
#define LIVES_OPTIONS_Y 				(NUM_LIVES_OPTION_TEXT_Y + 70)
#define LIVES_SELECTOR_Y 				(LIVES_OPTIONS_Y + 30)

// score display screen constants
#define SCORE_MAX_DIGITS 7
#define SCORE_LOGO_X LIVES_OPTIONS_LOGO_X
#define SCORE_LOGO_Y LIVES_OPTIONS_LOGO_Y
#define SCORE_TEXT_X 20
#define SCORE_TEXT_Y (SCORE_LOGO_Y + logo_small.height + 20)
#define LIVES_TEXT_X SCORE_TEXT_X
#define LIVES_TEXT_Y (SCORE_TEXT_Y + score_text.height + 20)
//#define SCORE_START_X (SCORE_TEXT_X + score_text.width)
#define SCORE_START_X (SCORE_TEXT_X + (score_text.width > lives_text.width ? score_text.width : lives_text.width))
#define SCORE_Y (SCORE_TEXT_Y + score_text.height - blue_nums[0]->height)
//#define LIVES_START_X (LIVES_TEXT_X + lives_text.width)
#define LIVES_START_X SCORE_START_X
#define LIVES_Y (LIVES_TEXT_Y + lives_text.height - red_nums[0]->height)

// list of all life option x values
extern uint8_t selector_x[];


//void init_led_spi(void);
// call this to initialize the lcd screen
void init_tft_lcd(void);

void clear_screen(void);

void start_menu_render(void);
void start_menu_options_render(void);
void score_display_render(GameState* gs);

void start_menu_update();
void start_menu_options_update();
void score_display_update(GameState* gs);


#endif
