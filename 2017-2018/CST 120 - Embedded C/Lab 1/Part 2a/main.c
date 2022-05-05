/*
 * Lab1p2a.c
 *
 * Created: 4/5/2018 11:41:43 AM
 * Author : zachery.rowland
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = (1 << DDB4);

	while (1)
	{
		PORTB = (1 << DDB4);
		_delay_ms(500);
		PORTB = 0;
		_delay_ms(500);
	}
}

