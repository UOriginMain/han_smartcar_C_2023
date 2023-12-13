/*
 * LcdDisplay.c
 *
 * Created: 13-12-2023 12:23:49
 *  Author: guusl
 */ 
#include "lcd.h"



extern void lcd_backlight(char on);    //not in lcd.h

void printWelcomeScreen(void) {
	lcd_clrscr();
	lcd_gotoxy(0, 0);
	lcd_puts_P("Team Antimotive");
	lcd_gotoxy(1, 1);
	lcd_puts("Debuggy");
}

void lcdDisplayInit(void) {
	 lcd_init(LCD_ON_DISPLAY);
	 lcd_backlight(0);
	 lcd_backlight(1);
	printWelcomeScreen();
}

