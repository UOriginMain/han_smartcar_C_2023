#define F_CPU (16000000UL)
#include <avr/io.h>
#include <avr/interrupt.h>
volatile uint32_t ms = 0;

void millis_init(void)
{
	ms = 0;
	// Configure Timer/counter 0 to generate an interrupt every millisecond
	//
	// - WGM0[2:0] = 010 : waveform generation mode is CTC with TOP in OCR0A
	// - CS0[2:0] = 011 : 64 prescaler
	// - TOP : 249
	//
	// T_events = T_CPU * N * (TOP + 1)
	// = 1/16 MHz * 64 * (249 + 1)
	// = 1 ms
	TCCR2A |= (1<<WGM01);
	TCCR2B |= (1<<CS01) | (1<<CS00);
	OCR2A = 249;
	// Timer/Counter0 Output Compare Match A Interrupt Enable
	TIMSK2 |= (1<<OCIE0A);
}

// Interrupt Service Routine that is automatically executed as soon as
// timer/counter 0 has reached its compare value
ISR(TIMER2_COMPA_vect)
{
	ms++;
}

uint32_t millis(void)
{
	// ms is a 32-bit variable (uint32_t). This means that multiple accesses
	// are needed to read or write the value of ms. There is a chance that
	// in the middle of these multiple accesses, the ms value is written due to
	// the ISR being triggered. In order to make sure the value of ms is not
	// updated when reading it, disable interrupts while reading the value.
	cli();
	uint32_t ret = ms;
	sei();
	return ret;
}