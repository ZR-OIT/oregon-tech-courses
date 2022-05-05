/*
 * Lab3p1.c
 *
 * Created: 4/19/2018 12:30:01 PM
 * Author : zachery.rowland
 */ 
//#define F_CPU 16000000UL

//#include <util/delay.h>
#include <avr/io.h>

#define LED_MASK 0x20
#define BUTTON_MASK1 0x10
#define BUTTON_MASK2 0x08

int main(void)
{
	DDRD = (0b111111 << DDB2);
	PORTB |= BUTTON_MASK1 | BUTTON_MASK2;

	while (1)
	{
		if((PINB & BUTTON_MASK2) == 0 || (PINB & BUTTON_MASK1) == 0)
		{
			PORTD = (0b111111 << DDB2);
		}
		else
		{
			PORTD = 0;
		}
	}
}

