/*
 * Motor.c
 *
 * Created: 21-1-2024 16:34:10
 *  Author: guusl
 */
#include <avr/io.h>


#define blinkerLeft DDD4
#define BlinkerRight DDD5

void motorFunctie(int speed, char dir) {
	switch (dir) {
		
		//forwards
		case 'F':
		//set both motors in forward mode
		PORTB |= (1<<DDB0);
		PORTD |= (1<<DDD7);
		
		//sets the motor speed
		OCR1A = speed;
		OCR1B = speed;
		break;
		
		
		//backwards
		case 'B':
		//set both motors in backwards mode
		PORTB &= ~(1<<DDB0);
		PORTD &= ~(1<<DDD7);
		
		//sets the motor speed
		OCR1A = speed;
		OCR1B = speed;
		break;
		
		
		//makes the car make a corner too the right
		case 'r':
		//set both motors in forward mode
		PORTB |= (1<<DDB0);
		PORTD |= (1<<DDD7);
		
		//sets the motor speed
		OCR1A = speed;
		OCR1B = speed/3;
		break;
		
		
		//makes the car turn around its axis too the right
		case 'R':
		//sets the motors on the rigt too backwards and the motors on the left too forward
		PORTB |= (1<<DDB0);
		PORTD &= ~(1<<DDD7);
		
		//sets the motor speed
		OCR1A = speed;
		OCR1B = speed;
		break;
		
		
		//makes the car make a corner too the left
		case 'l':
		//set both motors in forward mode
		PORTB |= (1<<DDB0);
		PORTD |= (1<<DDD7);
		
		//sets the motor speed
		OCR1A = speed/3;
		OCR1B = speed;
		break;
		
		
		//makes the car turn around its axis too the right
		case 'L':
		//sets the motors on the rigt too backwards and the motors on the left too forward
		PORTB = ~(1<<DDB0);
		PORTD |= (1<<DDD7);
		
		//sets the motor speed
		OCR1A = speed;
		OCR1B = speed;
		break;
		
		
		//the default makes the car stop
		default:
		//sets the pins too low
		PORTB &= ~(1<<DDB1);
		PORTB &= ~(1<<DDB2);
		//sets the compare too high so it won't set the pins too high
		OCR1A = 10000;
		OCR1B = 10000;
	}
} 

void motorInit(void) {
	DDRB |= (1<<DDB0) | (1<<DDB1) | (1<<DDB2);
	DDRD |= (1<<DDD7);
	// Configure Timer/counter 1 to generate an interrupt approximately every second
	//
	// For this configuration, several bits can keep their reset value.
	// This means that this function only implements instructions for bits
	// that must be updated.
	// Refer to the datasheet for a description of all the bits.
	// - WGM1[3:0] = 1110 : waveform generation mode is Fast PWM with TOP in ICR1
	// - CS1[2:0] = 011 : 64 prescaler
	//
	// TOP = (F_CPU / (F_PWM * N)) - 1
	// = (16MHz / (50Hz * 64)) - 1
	// = 4999
	TCCR1A |= (1<<WGM11);
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11) | (1<<CS10);
	ICR1 = 4999;
	// Set Compare Output Mode for both channels A and B
	// The mode is fast-PWM
	// COM1A[1:0] = 10 : Clear OC1A/OC1B on compare match, set OC1A/OC1B at
	// BOTTOM (non-inverting mode)
	// COM1B[1:0] = 11 : Set OC1A/OC1B on compare match, clear OC1A/OC1B at
	// BOTTOM (non-inverting mode)
	TCCR1A |= (1<<COM1A1) | (1<<COM1A0) | (1<<COM1B1) | (1<<COM1B0);		//sets the pins for the blinker left and right too outout	DDRD |= (1<<blinkerLeft) | (1<<BlinkerRight);}