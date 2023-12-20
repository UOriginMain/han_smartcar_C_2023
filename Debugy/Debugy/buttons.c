/*
 * buttons.c
 *
 * Created: 20-12-2023 10:45:49
 *  Author: guusl
 */ 
#include <avr/io.h>

#define scrollButton DDB2
#define selectResetButton DDD3


void buttonsInit() {
	//sets the pins so it are input pins
	DDRB &= ~(1<<scrollButton);
	DDRD &= ~(1<<selectResetButton);
	
	//temp for testing becuase this is for pull up
	PORTB |= (1<<PORTB2);
	PORTD |= (1<<PORTD3);
}

int scrollInMenu() {
	unsigned char buttonState = PINB & 0b00000100;
	if ((buttonState & (1<<scrollButton)) == 0) {
		return 1;
		} else {
		return 0;
	}
}

int selectMode() {
	unsigned char buttonState = PIND & 0b00001000;
	if ((buttonState & (1<<selectResetButton)) == 0) {
		return 1;
		} else {
		return 0;
	}
}