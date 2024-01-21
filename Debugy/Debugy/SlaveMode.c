/*
 * hoi134.c
 *
 * Created: 12-12-2023 14:54:21
 * Author : Big T
 */ 
#include <avr/io.h>

#define sensorOne PC0
#define sensorTwo PC1
#define sensorThree PC2
#define sensorFour PC3

//creates struct for the motor speed and direction
struct motorSettings  {
	int speed;
	char direction;
};

struct motorSettings motor;

void slaveModeInit(void) 
{

	DDRC &= ~((1 << sensorOne) | (1 << sensorTwo) | (1 << sensorThree) | (1 << sensorFour)); // Set PC0-PC3 as input
	PORTC |= (1 << sensorOne) | (1 << sensorTwo) | (1 << sensorThree) | (1 << sensorFour); // Enable pull-up resistors                                    
}


struct motorSettings slaveMode(void) {
	
		motor.speed = 3000;
		if(!(PINC & ((1 << sensorOne) | (1 << sensorTwo) | (1 << sensorThree) | (1 << sensorFour))))
		{
			//vooruit
			motor.direction = 'F';
			
		}
		
		else if(((PINC & (1 << sensorOne)) || (PINC & (1 << sensorTwo))) && !(PINC & (1 << sensorThree)) && !(PINC & (1 << sensorFour)))
		{
			//rects
			motor.direction = 'R';
		}
		
		else if(!(PINC & (1 << sensorOne)) && !(PINC & (1 << sensorTwo)) && ((PINC & (1 << sensorThree)) || (PINC & (1 << sensorFour))))
		{
			// links
			motor.direction = 'L';
		}
		else if((PINC & (1 << sensorOne)) && (PINC & (1 << sensorTwo)) && (PINC & (1 << sensorThree)) && (PINC & (1 << sensorFour)))
		{
			// vooruit
			motor.direction = 'F';
		}
	return  motor;
}


