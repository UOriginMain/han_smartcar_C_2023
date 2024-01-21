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
#include "Motor.h"

enum Modes {Slave, Bluetooth, Autonoom, Stop} mode;
	
//creates struct for the motor speed and direction	
struct motorSettings  {
	int speed;
	char direction;
};

//make a stucture variable of structure motorSettings
struct motorSettings motor;

long lastPrint = 0;
int firstPrint = 0;

void setup(void) {
	//init the different modules
	buttonsInit();
	millis_init();
	lcdDisplayInit();
	remoteControlInit();
	motorInit();

	//assings value to motor
	motor.speed = 0;
	motor.direction = 'S';
}

void loop(void) {
	if (scrollInMenu()) {
		if (firstPrint == 0) {
			firstPrint = 1;
		}
		
		if (mode < Autonoom) {
			mode++;
			} else if (mode == Autonoom) {
			mode = Slave;
			} else {
			mode = Stop;
		}
	}
	
	if ((lastPrint + 1000 < millis()) && firstPrint) {
		printModeScreen(mode);
		lastPrint = millis();
	}
	
	
	 if (selectMode()) {
		PORTB |= (1<<DDB5);
		} else if (scrollInMenu()) {
		PORTB |= (1<<DDB5);
		} 
	
	
	motor = remoteControl();
	motorFunctie(motor.speed, motor.direction);
}

int main(void)
{
	setup();
	DDRB |= (1<<DDB5);
	
	while (1) {
		loop();
	}
}



