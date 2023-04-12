#include "interfacing/scoreboard.h"

#include "stm32f0xx.h"

#include <hardware/TFT_LCD_lib.h>

#include "settings.h"

#include "assets.h"

void init_lcd_spi(void);

void init_tft_lcd() {
    init_lcd_spi();
    LCD_Setup();
}

void start_menu_render(void) {
	LCD_DrawFillRectangle(0, 0, LCD_H, LCD_W, BLACK);
	LCD_DrawPicture(0, 0, (const Picture*)&logo);
#if DEVICE_ID == PLAYER1
	LCD_DrawString(10,150, BLACK, WHITE, "Single", 16, 0);
	LCD_DrawString(270, 150, BLACK, WHITE, "Multi", 16, 0);

	LCD_DrawPicture(20, 150 + 25, (const Picture*)&selector_arrow);

#endif
#if DEVICE_ID == PLAYER2
#endif
}

void start_menu_options_render(void) {
	LCD_DrawFillRectangle(0, 0, LCD_H, LCD_W, BLACK);
	LCD_DrawPicture(0, 0, (const Picture*)&logo);
#if DEVICE_ID == PLAYER1
#endif
#if DEVICE_ID == PLAYER2
#endif
}

void score_display_render(void) {
#if DEVICE_ID == PLAYER1
#endif
#if DEVICE_ID == PLAYER2
#endif
}

void start_menu_update() {
#if DEVICE_ID == PLAYER1

#endif
#if DEVICE_ID == PLAYER2
	// do nothing because player 1 chooses the gamemode
#endif
}
void start_menu_options_update() {
#if DEVICE_ID == PLAYER1
#endif
#if DEVICE_ID == PLAYER2
#endif
}
void score_display_update(GameState* gs) {
#if DEVICE_ID == PLAYER1
	uint16_t multi_x = 20;
	uint16_t multi_y = 150 + 25;
	uint16_t single_x = 280;
	uint16_t single_y = 150 + 25;
	if(gs->is_multiplayer) {
		LCD_DrawFillRectangle(multi_x, multi_y, single_x + 20, single_y + 20, BLACK);
		LCD_DrawPicture(280, 150 + 25, (const Picture*)&selector_arrow);
	} else {
		LCD_DrawFillRectangle(single_x, single_y, single_x + 20, single_y + 20, BLACK);
		LCD_DrawPicture(20, 150 + 25, (const Picture*)&selector_arrow);

	}
#endif
#if DEVICE_ID == PLAYER2
#endif
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

