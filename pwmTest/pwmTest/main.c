#define F_CPU (16000000UL)
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	// PB0 - PB5 output, rest input
	DDRB = 0b00111111;
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
	// BOTTOM (inverting mode)
	TCCR1A |= (1<<COM1A1) | (1<<COM1B1) | (1<<COM1B0);
	
	// Set the initial duty cycle for both channels to 50%
	OCR1A = 0;
	OCR1B = 0;
	uint16_t cnt = 0;
	while (1)
	{
		// Gradually update the duty cycle by changing the
		// compare values every millisecond.
		// This takes a total of 5000 * 1ms = 5000ms = 5s.
		_delay_ms(1);
		if(cnt > 4999)
		{
			cnt = 0;
		}
		OCR1A = cnt;
		OCR1B = cnt;
	}
}