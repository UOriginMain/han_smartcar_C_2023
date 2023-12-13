/*
 * Debugy.c
 *
 * Created: 12-12-2023 14:32:06
 * Author :
 */ 

#include <avr/io.h>
#include "Millis.h"


#include <util/delay.h>
#include "lcd.h"
extern void lcd_backlight(char on);    //not in lcd.h


void buttonsInit();
int scrollInMenu();
int selectMode();

#define scrollButton DDB2
#define selectResetButtun DDD3



int main(void)
{
    /* Replace with your application code */
	buttonsInit();
	millis_init();
	lcd_init(LCD_ON_DISPLAY);
	lcd_backlight(1);
	
	DDRB |= (1<<DDB5);
	long milli = 0;
	
    while (1) 
    {
		selectMode();
		
		lcd_clrscr();
		lcd_gotoxy(5, 0);
		lcd_puts("Hello World");
		lcd_gotoxy(1, 1);
		lcd_puts("Hoi");
		lcd_puts(milli);
		_delay_ms(1000);
		
		milli = millis();
		
    }
}

void buttonsInit() {
	//sets the pins so it are input pins	
	DDRB &= ~(1<<scrollButton);
	DDRD &= ~(1<<selectResetButtun);
	
	//temp for testing becuase this is for pull up
	PORTB |= (1<<PORTB2);
	PORTD |= (1<<PORTD3);
}

int scrollInMenu() {
	unsigned char buttonState = PINB & 0b00000100; 
	if ((buttonState & (1<<DDB2)) == 0) {
			PORTB |= (1<<DDB5);
			return 1;
	} else {
		PORTB &= ~(1<<DDB5);
		return 0;
	}
}

int selectMode() {
	unsigned char buttonState = PIND & 0b00001000;
	if ((buttonState & (1<<DDD3)) == 0) {
		PORTB |= (1<<DDB5);
		return 1;
		} else {
		PORTB &= ~(1<<DDB5);
		return 0;
	}
}

