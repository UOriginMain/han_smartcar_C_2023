/*
* Debugy.c
*
* Created: 12-12-2023 14:32:06
* Author :
*/

#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>
#include "Millis.h"
#include "lcdDisplay.h"
#include "buttons.h"
#include "RemoteControl.h"

enum Modes {Slave, Bluetooth, Autonoom, Stop} mode;

long lastPrint = 0;

void setup(void) {
	buttonsInit();
	millis_init();
	lcdDisplayInit();
	
}

void loop(void) {
	if (scrollInMenu()) {
		if (mode < Autonoom) {
			mode++;
			} else if (mode == Autonoom) {
			mode = Slave;
			} else {
			mode = Stop;
		}
	}
	
	if (lastPrint + 1000 < millis()) {
		printModeScreen(mode);
		lastPrint = millis();
	}
	
	
	if (selectMode()) {
		PORTB |= (1<<DDB5);
		} else if (scrollInMenu()) {
		PORTB |= (1<<DDB5);
		} else {
		PORTB &= ~(1<<DDB5);
	}
	
}

int main(void)
{
	setup();
	DDRB |= (1<<DDB5);
	
	while (1) {
		loop();
	}
}



