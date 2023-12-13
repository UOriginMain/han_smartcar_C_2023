/*
 * Debugy.c
 *
 * Created: 12-12-2023 14:32:06
 * Author :
 */ 

#include <avr/io.h>
#include <stdio.h>

#include "Millis.h"
#include "lcdDisplay.h"




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
	lcdDisplayInit();
	
	char milli[10 + sizeof(char)];
	
	
	DDRB |= (1<<DDB5);
    while (1) 
    {
		selectMode();
		
		
		
		
	
		sprintf(milli, "%ld", millis());
		
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

