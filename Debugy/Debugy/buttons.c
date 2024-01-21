/*
 * buttons.c
 *
 * Created: 20-12-2023 10:45:49
 *  Author: guusl
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "Millis.h"

#define scrollButton DDD6
#define selectResetButton DDD3

volatile bool scrollButtonState = false;
volatile bool selectResetButtonState = false;

int lastSelectButtonPress = 0;
int lastScrollButtonPress = 0;

void buttonsInit() {
	//sets the pins so it are input pins
	DDRD &= ~(1<<scrollButton);
	DDRD &= ~(1<<selectResetButton);
	
	//enables the pin interupts
	PCICR |= (1<<PCIE2);
	//enables the exact pins for the interrupts
	PCMSK2 |= (1<<PCINT19) | (1<<PCINT22);
	
	//temp for testing because this is for pull up
	PORTD |= (1<<PORTD3) | (1<<PORTD6);
}

ISR(PCINT2_vect)
{
	if (((PIND & (1<<PIND3))==0) && (lastScrollButtonPress + 100 < millis())) {
		scrollButtonState = true;
	} else if (((PIND & (1<<PIND6)) == 0) && (lastSelectButtonPress + 100 < millis())) {
		selectResetButtonState = true;
	}
}

bool scrollInMenu() {
	if (scrollButtonState == true) {
		return true;
		scrollButtonState = false;
		lastScrollButtonPress = millis();
		} else {
		return false;  
	}
}

bool selectMode() {
	if (selectResetButtonState == 1) {
		return true;
		selectResetButtonState = 0;
		lastSelectButtonPress = millis();
		} else {
		return false;
	}
}