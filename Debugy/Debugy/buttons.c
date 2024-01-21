/*
 * buttons.c
 *
 * Created: 20-12-2023 10:45:49
 *  Author: guusl
 */ 
#include <avr/io.h>
#include "Millis.h"

#define scrollButton DDB2
#define selectResetButton DDD3

volatile int scrollButtonState = 0;
volatile int selectResetButtonState = 0;

int lastSelectButtonPress = 0;
int lastScrollButtonPress = 0;

void buttonsInit() {
	//sets the pins so it are input pins
	DDRB &= ~(1<<scrollButton);
	DDRD &= ~(1<<selectResetButton);
	
	//enables the pin interupts
	PCICR |= (1<<PCIE2) | (1<<PCIE0);
	//enables the exact pins for the interrupts
	PCMSK2 |= PCINT19;
	PCMSK0 |= PCINT3;
	
	//temp for testing because this is for pull up
	PORTB |= (1<<PORTB2);
	PORTD |= (1<<PORTD3);
}

ISR(PCINT0_vect)
{
	if ((scrollButtonState == 0) && (lastScrollButtonPress + 50 < millis())) {
		scrollButtonState = 1;
	}
}

/* ISR(PCINT1_vect)
{	
	if ((selectResetButtonState == 0) && (lastSelectButtonPress + 50 < millis())) {
	selectResetButtonState = 1;	
	}
}
*/

int scrollInMenu() {
	unsigned char buttonState = PINB & 0b00000100;
	if (scrollButtonState == 1) {
		return 1;
		scrollButtonState = 0;
		lastScrollButtonPress = millis();
		} else {
		return 0;
	}
}

int selectMode() {
	unsigned char buttonState = PIND & 0b00001000;
	if (selectResetButtonState == 1) {
		return 1;
		selectResetButtonState = 0;
		lastSelectButtonPress = millis();
		} else {
		return 0;
	}
}