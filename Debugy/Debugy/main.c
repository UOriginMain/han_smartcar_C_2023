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
#include "SlaveMode.h"

enum Modes {Slave, Bluetooth, Autonoom, Stop} mode;
int modeLock = 0;
	
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
	//lcdDisplayInit();
	millis_init();
	buttonsInit();
	remoteControlInit();
	motorInit();
	slaveModeInit();

	//assings value to motor
	motor.speed = 0;
	motor.direction = 'S';
	
	DDRB |= (1<<DDB4);
}

void loop(void) {
	if (modeLock == 1) {
		switch (mode) {
			case Autonoom:
			motor.speed = 3000;
			motor.direction = 'F';
			break;
			
			case Slave:
			motor = slaveMode();
			
			break;
			
			case Bluetooth:
			motor = remoteControl();
			break;	
		}
	}
	
	if (scrollInMenu() && (modeLock == 0)) {
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
		lastPrint = millis();
		if (modeLock == 1) {
			printModeScreen(mode);
		} else if (modeLock == 0) {
			printMenuScreen(mode);
		}
	}
	
	
	 if (selectMode()) {
		 if (modeLock == 1) {
			 modeLock = 0;
			 motor.speed = 0;
		 } else if (modeLock == 0) {
			 modeLock = 1;
		} 
	 }
	
	motorFunctie(motor.speed, motor.direction);
}

int main(void)
{
	setup();
	

	while (1) {
		loop();
		scrollInMenu();
	}
}



