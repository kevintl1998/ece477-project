#include "interfacing/scoreboard.h"

#include "stm32f0xx.h"

#include <hardware/TFT_LCD_lib.h>

#include "settings.h"
#include "util.h"
#include "assets.h"

// list of all life option x positions
uint8_t selector_x[] = {LIVES_OPTION_1_X, LIVES_OPTION_3_X, LIVES_OPTION_5_X, LIVES_OPTION_10_X };

const Picture* blue_nums[] = { (const Picture*)&blue0, (const Picture*)&blue1, (const Picture*)&blue2, (const Picture*)&blue3, (const Picture*)&blue4, (const Picture*)&blue5, (const Picture*)&blue6, (const Picture*)&blue7, (const Picture*)&blue8, (const Picture*)&blue9 };
const Picture* red_nums[] = { (const Picture*)&red0, (const Picture*)&red1, (const Picture*)&red2, (const Picture*)&red3, (const Picture*)&red4, (const Picture*)&red5, (const Picture*)&red6, (const Picture*)&red7, (const Picture*)&red8, (const Picture*)&red9 };

void init_lcd_spi(void);
void display_digits(uint32_t number, const Picture*(* numPic_arr), uint32_t start_x, uint32_t y);

void init_tft_lcd() {
    init_lcd_spi();
    LCD_Setup();
}

void clear_screen(void) {
	LCD_DrawFillRectangle(0, 0, LCD_H, LCD_W, BLACK);
}

void start_menu_render(void) {


	clear_screen();

	LCD_DrawPicture(GAMEMODE_SELECT_LOGO_X, GAMEMODE_SELECT_LOGO_Y, (const Picture*)&logo_small);
	LCD_DrawPicture(SINGLE_TEXT_X, SINGLE_TEXT_Y, (const Picture*)&fancy_single);
	LCD_DrawPicture(MULTI_TEXT_X, MULTI_TEXT_Y, (const Picture*)&fancy_multi);
	LCD_DrawPicture(CORNER_SUN_X, CORNER_SUN_Y, (const Picture*)&corner_sun);

	LCD_DrawPicture(GAMEMODE_SELECTOR_SINGLE_X, GAMEMODE_SELECTOR_Y, (const Picture*)&selector_arrow);

}

void start_menu_options_render(void) {
	clear_screen();

	LCD_DrawPicture(LIVES_OPTIONS_LOGO_X, LIVES_OPTIONS_LOGO_Y, (const Picture*)&logo_small);
	LCD_DrawPicture(NUM_LIVES_OPTION_TEXT_X, NUM_LIVES_OPTION_TEXT_Y, (const Picture*)&number_of_lives);
	LCD_DrawPicture(LIVES_OPTION_1_X, LIVES_OPTIONS_Y, (const Picture*)&white1);
	LCD_DrawPicture(LIVES_OPTION_3_X, LIVES_OPTIONS_Y, (const Picture*)&white3);
	LCD_DrawPicture(LIVES_OPTION_5_X, LIVES_OPTIONS_Y, (const Picture*)&white5);
	LCD_DrawPicture(LIVES_OPTION_10_X, LIVES_OPTIONS_Y, (const Picture*)&white1);
	LCD_DrawPicture(LIVES_OPTION_10_X + 10, LIVES_OPTIONS_Y, (const Picture*)&white0);

	LCD_DrawPicture(LIVES_OPTION_1_X, LIVES_SELECTOR_Y, (const Picture*)&selector_arrow);
}

void score_display_render(GameState* gs) {
	clear_screen();

	LCD_DrawPicture(SCORE_LOGO_X, SCORE_LOGO_Y, (const Picture*)&logo_small);

	LCD_DrawPicture(SCORE_TEXT_X, SCORE_TEXT_Y, (const Picture*)&score_text);
	LCD_DrawPicture(LIVES_TEXT_X, LIVES_TEXT_Y, (const Picture*)&lives_text);
	LCD_DrawPicture(SCORE_START_X, SCORE_Y, (const Picture*)blue_nums[0]);
	LCD_DrawPicture(LIVES_START_X, LIVES_Y, (const Picture*)red_nums[0]);
}

void gameover_render(GameState* gs) {
	if(gs->gameMode == GAMEMODE_MULTIPLAYER) {
		// display multiplayer game end screen
		// display winner or loser
		if(gameState->other_lives == gameState->lives_left) {
			LCD_DrawString(0,0,WHITE,BLACK,"its a tie!",16,0);
		} else if(gameState->other_lives == 0) {
			LCD_DrawString(0,0,WHITE,BLACK,"you win!",16,0);
		} else {
			LCD_DrawString(0,0,WHITE,BLACK,"you lose :(", 16, 0);
		}

		// display your score and opponents score
	} else {
		// display singleplayer game end screen
		LCD_DrawString(0,0,WHITE,BLACK,"insert score here", 16,0);
	}
}

void start_menu_update(GameState* gs) {
	if(gs->gameMode) {
		LCD_DrawFillRectangle(GAMEMODE_SELECTOR_SINGLE_X, GAMEMODE_SELECTOR_Y, GAMEMODE_SELECTOR_SINGLE_X + selector_arrow.width, GAMEMODE_SELECTOR_Y + selector_arrow.height, BLACK);
		LCD_DrawPicture(GAMEMODE_SELECTOR_MULTI_X, GAMEMODE_SELECTOR_Y, (const Picture*)&selector_arrow);
	} else {
		LCD_DrawFillRectangle(GAMEMODE_SELECTOR_MULTI_X, GAMEMODE_SELECTOR_Y, GAMEMODE_SELECTOR_MULTI_X + selector_arrow.width, GAMEMODE_SELECTOR_Y + selector_arrow.height, BLACK);
		LCD_DrawPicture(GAMEMODE_SELECTOR_SINGLE_X, GAMEMODE_SELECTOR_Y, (const Picture*)&selector_arrow);

	}
}

void start_menu_options_update(GameState* gs) {
	for(int i = 0; i < 4; i++) {
		if(gs->lives_option == i) {
			LCD_DrawPicture(selector_x[i], LIVES_SELECTOR_Y, (const Picture*)&selector_arrow);
		} else {
			LCD_DrawFillRectangle(selector_x[i], LIVES_SELECTOR_Y, selector_x[i] + selector_arrow.width, LIVES_SELECTOR_Y + selector_arrow.height, BLACK);
		}
	}
}

// displays digits of number on screen using the pictures in numPic_arr
void display_digits(uint32_t number, const Picture*(* numPic_arr), uint32_t start_x, uint32_t y) {
	uint32_t digit_arr[SCORE_MAX_DIGITS] = { 0 };
	uint32_t digits = digits_to_arr(number, digit_arr, SCORE_MAX_DIGITS);
	for(int i = digits - 1; i >= 0; i--) {
		const Picture* digit = numPic_arr[digit_arr[i]];
		LCD_DrawPicture(start_x, y, digit);
		start_x += digit->width;
	}
    LCD_DrawFillRectangle(start_x, y, SCOREBOARD_WIDTH, y + numPic_arr[0]->height, BLACK);
}

void score_display_update(GameState* gs) {
    // update score
    display_digits(gs->score, blue_nums, SCORE_START_X, SCORE_Y);

    // update lives
    display_digits(gs->lives_left, red_nums, LIVES_START_X, LIVES_Y);

}


void init_lcd_spi(void) {
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

    GPIOB->MODER |= (1<<(8*2)) | (1<<(11*2)) | (1<<(14*2)); // PB8,PB11,PB14 => output

    GPIOB->BSRR = 0x4900;

    GPIOB->MODER |= (2<<(3*2)) | (2<<(5*2)); // PB3,PB5 => alternate function

    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    SPI1->CR1 &= ~SPI_CR1_SPE;
    SPI1->CR1 &= ~(SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_BR_2);
    SPI1->CR1 |= SPI_CR1_MSTR;
    SPI1->CR2 = SPI_CR2_DS_0 | SPI_CR2_DS_1 | SPI_CR2_DS_2;
    SPI1->CR1 |= SPI_CR1_SSM;
    SPI1->CR1 |= SPI_CR1_SSI;
    SPI1->CR1 |= SPI_CR1_SPE;
}

