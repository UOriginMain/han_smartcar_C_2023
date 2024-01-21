/*
 * LcdDisplay.c
 *
 * Created: 13-12-2023 12:23:49
 *  Author: guusl
 */ 

#include <avr/io.h>
#include "lcd.h"

enum Modes {Slave, Bluetooth, Autonoom};	

extern void lcd_backlight(char on);    //not in lcd.h

void printWelcomeScreen(void) {
	lcd_clrscr();
	lcd_gotoxy(0, 0);
	lcd_puts_P("Debuggy");
	lcd_gotoxy(0, 1);
	lcd_puts("Team Antimotive"); 
}

void lcdDisplayInit(void) {
	 lcd_init(LCD_ON_DISPLAY);
	 lcd_backlight(0);
	 lcd_backlight(1);
	 printWelcomeScreen();
}

void printModeScreen(enum Modes mode) {
	switch (mode) {
		case Slave:
		lcd_clrscr();
		lcd_gotoxy(1, 1);
		lcd_puts("Slave");
		break;
		
		case Bluetooth:
		lcd_clrscr();
		lcd_gotoxy(1, 1);
		lcd_puts("Bluetooth");
		break;
		
		case Autonoom:
		lcd_clrscr();
		lcd_gotoxy(1, 1);
		lcd_puts("Autonoom");
		break;
		
		default:
		lcd_clrscr();
		lcd_gotoxy(1,1);
		lcd_puts("hoe kom jij hier");
	}
}

void printMenuScreen(enum Modes mode) {
	switch (mode) {
		case Slave:
		lcd_clrscr();
		lcd_gotoxy(1, 1);
		lcd_puts("Slave");
		break;
		
		case Bluetooth:
		lcd_clrscr();
		lcd_gotoxy(1, 1);
		lcd_puts("Bluetooth");
		break;
		
		case Autonoom:
		lcd_clrscr();
		lcd_gotoxy(1, 1);
		lcd_puts("Autonoom");
		break;
		
		default:
		lcd_clrscr();
		lcd_gotoxy(1,1);
		lcd_puts("hoe kom jij hier");
	}
}

void print(int speed, char dir) {
	lcd_clrscr();
	lcd_gotoxy(0, 1);
	lcd_puts("Autonoom");
	lcd_gotoxy(1,0);
	lcd_puts(speed);
	lcd_puts(dir);	 
	 
 }
