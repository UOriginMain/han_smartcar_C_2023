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

void remoteControlInit(void) {
	SoftSerialInit();
}

void remoteControl(void)
{
	sei();
		
	if(SoftSerialUnread() > 0)
	{
		char data = SoftSerialReceiveByte();
			
		switch( data )
		{

			case '1':
			break;
			
			case 'h':
			break;

			case 'H':
			break;

			default:
			break;
		}

	}
}

