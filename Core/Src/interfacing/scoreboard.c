#include "interfacing/scoreboard.h"
#include "settings.h"
#include "hardware/TFT_LCD_legacy.h"
//#include <stdbool.h>

#define PIC_WIDTH 3
#define PIC_HEIGHT 3
unsigned char multi_picture[PIC_WIDTH * PIC_HEIGHT * 3] = {255, 0, 0,
		0, 255, 0,
		0, 0, 255,
		0, 0, 255,
		255, 0, 0,
		0, 255, 0,
		0, 255, 0,
		0, 0, 255,
		255, 0, 0};

Picture multi;

void start_menu_render(void) {
	LCD_DrawFillRectangle(0, 0, LCD_H, LCD_W, WHITE);
#if DEVICE_ID == PLAYER1
	LCD_DrawString(10,200, BLACK, WHITE, "Single", 16, 0);
	LCD_DrawString(270, 200, BLACK, WHITE, "Multi", 16, 0);
	multi.width = PIC_WIDTH;
	multi.height = PIC_HEIGHT;
	multi.bytes_per_pixel = 3;
	multi.pixel_data = multi_picture;
	LCD_DrawPicture(0, 0, &multi);
#endif
#if DEVICE_ID == PLAYER2
#endif
}


void start_menu_options_render(void) {
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
