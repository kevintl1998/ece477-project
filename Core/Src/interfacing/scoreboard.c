#include "interfacing/scoreboard.h"
#include "settings.h"
#include "hardware/TFT_LCD_legacy.h"

void start_menu_render(void) {
	LCD_DrawFillRectangle(0, 0, LCD_H, LCD_W, WHITE);
#if DEVICE_ID == PLAYER1
	LCD_DrawString(10,200, BLACK, WHITE, "Single", 16, 0);
	LCD_DrawString(270, 200, BLACK, WHITE, "Multi", 16, 0);

	// example function call
//	LCD_DrawPicture(0, 0, (const Picture*)&image);
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
