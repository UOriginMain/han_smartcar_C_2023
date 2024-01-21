	/*
	* RemoteControl.c
	*
	* Created: 19-1-2024 12:54:58
	*  Author: guusl
	*/
	/*
	* main.c
	*
	* Created: 21-9-2021 20:06:52
	* Author : Hugo Arends
	*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "SoftSerial.h"


//creates struct for the motor speed and direction
struct motorSettings  {
	int speed;
	char direction;
};

void remoteControlInit(void) {
	SoftSerialInit();
}

struct motorSettings remoteControl(void)
{
	sei();
	//make a stucture variable of structure motorSettings
	struct motorSettings motor;
		
	if(SoftSerialUnread() > 0)
	{
		char data = SoftSerialReceiveByte();
			
		switch( data )
		{
			case 'F':
			motor.direction = 'F';
			motor.speed = 3000;
			break;
			
			case 'S':
			motor.direction = 'S';
			motor.speed = 0;
			break;
			
			case 'R':
			motor.direction = 'r';
			motor.speed = 3000;
			break;
			
			case 'L':
			motor.direction = 'l';
			motor.speed = 3000;
			break;
			
			case 'B':
			motor.direction = 'B';
			motor.speed = 3000;
			break;
			
			case 'T':
			motor.direction = 'L';
			motor.speed = 2500;
			break;
			
			case 't':
			motor.direction = 'R'
			motor.speed = 2500;
			break
			
			case 'V':
			motor.speed += 250;
			break;
			
			case 'v':
			motor.speed -= 250;
			break;			
		}
	}
	return motor;
}

